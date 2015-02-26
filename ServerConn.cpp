 #include "stdafx.h"
#include "EventArgs.h"
#include "RecieveEventArgs.h"
#include "EventHandler.h"
#include "Debug.h"
#include "ServerConn.h"

#define SERVERCONN_CONNECTION_RECIEVE 394981
#define SERVERCONN_CONNECTED_EVENT 162746
namespace Osaka{
	namespace Network{

		//when called, ptr holds the instance of DebugClient
		static DWORD WINAPI ServerConn_StartThreadRun(LPVOID ptr)  
		{
			static_cast<ServerConn*>(ptr)->ThreadRun();
			return 0;
		}
		static DWORD WINAPI ServerConn_StartPing(LPVOID ptr)  
		{
			static_cast<ServerConn*>(ptr)->Ping();
			return 0;
		}
		//This is needed so I can access the DebugClient (this)
		//Source: http://stackoverflow.com/questions/14661865/use-object-method-as-winapi-wndproc-callback
		LRESULT CALLBACK ServerConn_StaticWinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam){
			ServerConn *d = (ServerConn*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
			if (d == NULL)
				return DefWindowProc(hWnd, msg, wParam, lParam);
	
			return d->WinProc(hWnd, msg, wParam, lParam);
		}

		ServerConn::ServerConn(Debug::DebugPTR& debug){
			//HWND this is the handle so I can catch the socket messages
			hwnd = NULL;
	
			//This is the thread the socket runs on
			thread = NULL;

			//This is the thread that send the pings every 1 second
			pingThread = NULL;
	
			//This is the socket (connection with the server)
			connection = INVALID_SOCKET;
			connIsUp = false;

			InitializeCriticalSection(&this->csCleanup);
			this->ConnectionRecieveEventPTR = std::make_shared<Component::EventHandler>();
			this->ConnectionRecieveEventPTR->Hook(SERVERCONN_CONNECTION_RECIEVE+99, std::bind(&ServerConn::RecieveEvent, this, std::placeholders::_1));

			state.bytes_read = 0;
			//no performance hit
			state.data.reserve(DEFAULT_BUFLEN*2);
			state.data = "";

			this->ConnectedEventPTR = std::make_shared<Component::EventHandler>();

			this->debug = debug;
		}

		ServerConn::~ServerConn(){
#ifdef _DEBUG
			_CHECKDELETE("ServerConn");
#endif
			this->ConnectionRecieveEventPTR->Unhook(SERVERCONN_CONNECTION_RECIEVE+99);

			ConnectionRecieveEventPTR = nullptr;;
			ConnectedEventPTR = nullptr;

			this->Stop(true);
			DeleteCriticalSection(&this->csCleanup);
		}
		void ServerConn::_delete(){
			debug = nullptr;
		}
		bool ServerConn::isConnected(){
			return connIsUp;
		}

		void ServerConn::Start(){
			this->Stop();
	
			if( pingThread == NULL ){
				ServerConn* c = this;
				this->ConnectedEventPTR->Hook(SERVERCONN_CONNECTED_EVENT+2, [c](Component::EventArgs& e){
					c->pingThread = CreateThread(NULL, 0, &ServerConn_StartPing, c, 0, NULL);
				});
			}
		
			thread = CreateThread(NULL, 0, &ServerConn_StartThreadRun, this, 0, NULL);
		}

		//Function that runs in a separate thread
		void ServerConn::ThreadRun(){
			//I don't know why it has to be created on the same thread as the loop
			this->CreateWindowHWND(); 
			if( !this->Connect() ){
				this->CleanupConnection();
			}
			ConnectedEventPTR->Raise(Component::EmptyEventArgs);
			MSG msg;
			ZeroMemory(&msg, sizeof(MSG));
	
			while( GetMessage(&msg, NULL, 0, 0) ){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		void ServerConn::Ping(){
			//This function will always be called because if you see ConnectedEvent.raise() will be called regardless if this->Connect() returns true
			this->ConnectedEventPTR->Unhook(SERVERCONN_CONNECTED_EVENT+2);
			HANDLE hConnectedEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("DebugClient_Ping_ConnectedEvent"));
			while(connIsUp){
				this->Send("~client-im-here");
				//TODO: I could use instead Sleep(milliseconds)
				(DWORD)WaitForSingleObject(hConnectedEvent, DEBUG_PING); //Always wait 2 second
			}
	
			CloseHandle(hConnectedEvent);
		}

		bool ServerConn::StartAndWaitForConnection(){
	
			HANDLE hConnectedEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("DebugClient_Stop_ConnectedEvent"));
			this->ConnectedEventPTR->Hook(SERVERCONN_CONNECTED_EVENT+1, [hConnectedEvent](Component::EventArgs& e){
				SetEvent(hConnectedEvent);
			});

			this->Start();

			if( (DWORD)WaitForSingleObject(hConnectedEvent, 1000) == WAIT_OBJECT_0 ){
				//ret = true;
			}
			this->ConnectedEventPTR->Unhook(SERVERCONN_CONNECTED_EVENT+1);
			CloseHandle(hConnectedEvent);

			return connIsUp;
		}

		void ServerConn::Stop(){
			this->Stop(false);
		}
		//This method should not be called inside the other thread
		void ServerConn::Stop(bool skipSend){
			bool tempConnIsUp = connIsUp;

			if( connIsUp && skipSend == false ){
				HANDLE hRecieveEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("DebugClient_Stop_RecieveEvent"));
				this->ConnectionRecieveEventPTR->Hook(SERVERCONN_CONNECTION_RECIEVE+1, [hRecieveEvent](Component::EventArgs& e){
					RecieveEventArgs& re = (RecieveEventArgs&)e;
					if( re.find("~bye") ){
						SetEvent(hRecieveEvent);
					}
				});

				if( this->Send("~close-connection") ){
					debug->localL("[ServerConn]  Waiting on server to reply bye...");
					if( (DWORD)WaitForSingleObject(hRecieveEvent, 1000) != WAIT_OBJECT_0 ){
						debug->localL("[ServerConn]  Server didn't reply \"~bye\"");
					}
				}

				this->ConnectionRecieveEventPTR->Unhook(SERVERCONN_CONNECTION_RECIEVE+1);
				CloseHandle(hRecieveEvent);
			}
	
			this->CleanupConnection();

			if( hwnd != NULL ){
				debug->localL("[ServerConn]  Waiting on the window to close...");
				SendMessage(hwnd, WM_CLOSE, NULL, NULL); //there is also WM_QUIT, WM_DESTROY
				//CloseHandle(hwnd); //I guess someone else calls it.
				hwnd = NULL;
			}

			if( thread != NULL ){
				debug->localL("[ServerConn]  Waiting for thread to end...");
				WaitForSingleObject(thread, INFINITE);
				CloseHandle(thread);

				thread = NULL;
			}

			if( pingThread != NULL){
				debug->localL("[ServerConn]  Waiting for ping thread to end...");
				WaitForSingleObject(pingThread, INFINITE);
				CloseHandle(pingThread);
				pingThread = NULL;
			}

			if( tempConnIsUp )
				debug->localL("[ServerConn]  Connection stopped.");
		}

		void ServerConn::CleanupConnection(){
			//This method is called in Stop() and the message queue loop
			//Instead of stopping everything like in Stop()
			//I will just close the connection

			connIsUp = false;
			//This critical section might not be needed because socket operations are thread safe (right?)
			EnterCriticalSection(&this->csCleanup);
			if( connection != INVALID_SOCKET ){
				shutdown(connection, SD_BOTH);
				closesocket(connection);
				connection = INVALID_SOCKET;
				debug->localL("[ServerConn]  Cleanup Connection.");
			}
			WSACleanup();
			LeaveCriticalSection(&this->csCleanup);

		}

		//Pass string by value. Not reference because we are modifying the string.
		bool ServerConn::Send(std::string msg){
			if( !this->connIsUp ) 
				return false;
	
			//This is my message -> 00000This is my message
			msg.insert(0, MESSAGE_PACKET_STR);
			int size = msg.size();

			char buffer[MESSAGE_PACKET_SIZE+1]; //You need 2 extra spaces for \n
			//23
			_itoa_s(size, buffer, 10);
	
			int len = strlen(buffer);
			//->00023This is my message
			msg.replace(MESSAGE_PACKET_SIZE-len, len, std::string(buffer));
	
			const char* temp = msg.c_str();
			int iResult;
			do{
				iResult = send(this->connection, temp, (int)strlen(temp), 0);
				if( iResult == SOCKET_ERROR ){
					int last_error = WSAGetLastError();
					if( last_error == WSAEWOULDBLOCK ){
						//This means there is a bottleneck?
						//Wait until it the socket is available
						debug->localL("[ServerConn]  Socket is not available. Waiting 25 ms...");
						Sleep(50);
						continue;
					}else{
						debug->localL((std::string("[ServerConn]  Send failed with error: ")+std::to_string(last_error)).c_str());
						this->CleanupConnection();
						return false;
					}
				}else{
					//Send was succesful
					break;
				}
			}while(true);
	
			//printf("[ServerConn]  Sent %s\n", temp);
			return true;
		}

		bool ServerConn::Send(const char* message){
			if( !this->connIsUp ) 
				return false;
			return this->Send(std::string(message));
		}

		LRESULT CALLBACK ServerConn::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			switch(msg){
			case WM_CREATE:
				//This is never called because you need to create the window first then set the windowlongptr
			break;	
			case WM_SIZE:
				//printf("test: resize");
				break;
			case WM_SOCKET:
				if( WSAGETSELECTERROR(lParam) ){
					debug->localL("[ServerConn]  WSAGETSELECTERROR");
					this->CleanupConnection(); //silently cleanup connection
					break;
				}

				switch(WSAGETSELECTEVENT(lParam)){
				case FD_READ:{
					//This is the only way to recieve messages with non-blocking sockets
					char recvbuf[DEFAULT_BUFLEN];
					int recvbuflen = DEFAULT_BUFLEN;
					ZeroMemory(recvbuf, sizeof(recvbuf));

					//You can't use `recv` outside of the message queue loop
					int res = recv(connection, recvbuf, recvbuflen, 0);
					if( !(res > 0) ){
						//if res == 0 it means the connection was closed.
						//else
						//printf("[ServerConn]  recv failed with error: %d\n", WSAGetLastError());
						debug->localL("[ServerConn] recv error");
						this->CleanupConnection();
						break;
					}

					//------------------------------------------------------------------------------------------------
					//Vector is better because the items are sequentially added. (Less cache miss)
					std::vector<std::string> messages;
					messages.reserve(5);
			
					state.data.append(recvbuf);
					state.bytes_read += res;
					do{
						if( state.data.length() >= MESSAGE_PACKET_SIZE ){
							//It means we have at least 00000 size
							int size = std::stoi(state.data.substr(0, MESSAGE_PACKET_SIZE));
							if( state.bytes_read >= size ){
								//We have one full message.
								state.bytes_read -= size;
								//This works because every char is 1 byte
								messages.push_back(state.data.substr(MESSAGE_PACKET_SIZE, size - MESSAGE_PACKET_SIZE));

								if( state.bytes_read > 0 ){
									state.data.erase(MESSAGE_PACKET_SIZE, state.data.length() - size);
									//There are more bytes to read
									//No break
								}else if( state.bytes_read == 0 ){
									//No more bytes to read.
									state.data.clear();
									break;
								}
							}else{
								//We haven't recieved the full message (bytes)
								break;
							}
						}else{
							//We haven't recieved at least the first 5 -> 00000
							break;
						}
					}while(true);

					if( messages.size() > 0 ){
						RecieveEventArgs* e = new RecieveEventArgs(&messages);
						//&e is the address of the pointer. *e is the address where it is pointing
						ConnectionRecieveEventPTR->Raise(*e);
						//I can do this because .raise() and the calls are called in this same thread.
						//When it gets to `delete e`, nothing bad will happen.
						//Otherwise (raising in another thread), I would need a lock here.
						delete e;
					}
					//------------------------------------------------------------------------------------------------
			
					break;}
				case FD_CLOSE:{
					debug->localL("[ServerConn] Message queue loop > FD_CLOSE");
					this->CleanupConnection();
					break;}
				}
			break;
			case WM_DESTROY:
				PostQuitMessage(WM_QUIT);
				return 0;
				break;
			default:
				//return DefWindowProc(hwnd, msg, wParam, lParam);
				break;
			}

			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		void ServerConn::RecieveEvent(Component::EventArgs& e){
			RecieveEventArgs& re = (RecieveEventArgs&)e;

			//This message is handled in Stop()
			//if( strcmp(re.message, "~bye") == 0 ){ }

			for(std::size_t i = 0; i != re.messages->size(); i++) {
				const char* str = re.messages->at(i).c_str();
		
				if( strcmp(str, "~server-im-here") == 0 ){
					//do nothing
				}else if( strcmp(str, "~hello-client") == 0 ){
					debug->l("[ServerConn]  Server replied with hello client\n");
				}else if( strcmp(str, "~close-connection") == 0 ){
					this->Send("~bye");
				}else{
					//All log (if there is a connection) must be passed to the server.
					//If for any reason the server disconnects after recieving the message then log it to console or file
					if( !this->Send((std::string("[ServerConn]  Server says: ") + std::string(str)).c_str()) ){
						debug->localL((std::string("[ServerConn]  Reciprocate send failed. Server says: ") + std::string(str)).c_str());
					}
				}
			}
	
		}

		bool ServerConn::Connect(){
			if( connection != INVALID_SOCKET ){
				debug->localL("[ServerConn]  Connection is up?");
				return true;
			}

			connIsUp = false;
			int iResult;

			WSADATA wsaData;
			connection = INVALID_SOCKET;
			struct addrinfo *result = NULL, *ptr = NULL, hints;

			iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
			if( iResult != 0 ){
				debug->localL((std::string("[ServerConn]  WSAStartup failed with error: ")+std::to_string(iResult)).c_str());
				return false;
			}

			ZeroMemory(&hints, sizeof(hints));
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;

			iResult = getaddrinfo("127.0.0.1", "6661", &hints, &result);
			if( iResult != 0 ){
				debug->localL((std::string("[ServerConn]  getaddrinfo failed with error: ")+std::to_string(iResult)).c_str());
				WSACleanup();
				return false;
			}

			for(ptr=result; ptr != NULL; ptr=ptr->ai_next){
				connection = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
				if( connection == INVALID_SOCKET ){
					debug->localL((std::string("[ServerConn]  socket failed with error: ")+std::to_string(WSAGetLastError())).c_str());
					WSACleanup();
					return false;
				}

				iResult = connect(connection, ptr->ai_addr, (int)ptr->ai_addrlen);
				if( iResult == SOCKET_ERROR ){
					closesocket(connection);
					connection = INVALID_SOCKET;
					continue;
				}
				break;
			}

			freeaddrinfo(result); //This isn't needed to be called if WSACleanup() is called (I think so)
	
			if( connection == INVALID_SOCKET ){
				debug->localL("[ServerConn]  Unable to connect to server");
				WSACleanup();
				return false;
			}
	
			//Async
			//I could add `|FD_CONNECT` but... Connect()[this method] is called before the message queue loop...
			iResult = WSAAsyncSelect(connection, hwnd, WM_SOCKET, (FD_CLOSE|FD_READ));
			if( !(iResult == 0) ){
				std::string error_str = "[ServerConn]  WSAAsyncSelect failed with error:";
				error_str += std::to_string(iResult);
				error_str += " WSALastError: ";
				error_str += std::to_string(WSAGetLastError());
				debug->localL(error_str.c_str());
				closesocket(this->connection);
				WSACleanup();
				return false;
			}

			connIsUp = true;
			//Send the first hello message
			this->Send("~hello-server");
			debug->l("[ServerConn]  Connected to server.");
			return true;
		}

		void ServerConn::CreateWindowHWND(){
			if( hwnd != NULL ){
				debug->localL("[ServerConn]  hwnd is not null!");
				return;
			}
			WNDCLASSEX wc;
			ZeroMemory(&wc, sizeof(WNDCLASSEX));

			HINSTANCE hInst = GetModuleHandle(0);

			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = ServerConn_StaticWinProc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
			wc.lpszMenuName = NULL;
			wc.lpszClassName = L"ServerConnSocketCN";
			wc.hInstance = hInst;
			wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

			RegisterClassEx(&wc);
	
			//hwnd = CreateWindowA("DebugSocketCN","DebugSocket",NULL,0,0,100,100,NULL,NULL,NULL,NULL);
			hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"ServerConnSocketCN", L"ServerConnSocketCN", WS_OVERLAPPEDWINDOW, 5, 580, 100, 100, NULL, NULL, hInst, NULL);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
			UpdateWindow(hwnd);

			//ShowWindow(hwnd, SW_SHOWDEFAULT);
		}
	}
}