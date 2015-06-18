 #include "stdafx.h"

#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

//This is the ID message to catch the message in the queue (WinProc)
#define WM_SOCKET		6661
//It is exactly 1024. I didn't increment it because 1024 INCLUDING \n
#define DEFAULT_BUFLEN 1024
#define DEBUG_PING 2000
//This is the paddings to know the bytes of the message: 00023This is my message
#define MESSAGE_PACKET_SIZE 5
#define MESSAGE_PACKET_STR "00000"

//Forward declarations. Unfortunately, it's easier to make them pointers
namespace Osaka{
	namespace Component{
		class EventHandler;
		class EventArgs;
	}
	namespace Debug{
		class Debug;
	}
}

namespace Osaka{
	namespace Network{

		//This is the data state. See Recieve (WinProc -> RD_READ)
		struct DataState{
			DataState(){};
			//Strings are mutable so isn't much of a performance hit
			std::string data;
			int bytes_read; //0
		};

		/*
			* This class may not be 100% thread safe but the socket functions are thread-safe.
			* Before trying and fix the race condition problems, try to get the error first, instead of pre-mature solving problems that may never happen.
			*		- I say this because I have yet to learn more but it is good enough.
			*		- I did a test with ping every 1ms and when I closed the connection (c++ side), nothing bad happened.
			*		- I did a test with ping every 1ms and I closed the connection (c# server side), nothing bad happened.
		*/
		class ServerConn
		{
		public:
			ServerConn(Debug::Debug* debug);
			~ServerConn();
			
			void Start();
			bool StartAndWaitForConnection();
			//Runs on a separate thread
			void ThreadRun();
			//Runs on a separate thread
			void Ping();
			//Runs on a separate thread
			//It is not necessary to wrap this funcion with CriticalSection because it is a message queue loop
			LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			//This is the internal function (for the connection recieve event)
			void RecieveEvent(Component::EventArgs& e);
			void Stop();
			//skipSend = true when called by the GC (~DebugClient())
			void Stop(bool skipSend);
	
			bool Send(const char* message);
			bool Send(std::string msg);
			bool isConnected();

			//MEMBERS -------------------------------------------------------------
			//This is the event when someone has been recieved. See WinProc->FD_Read
			Component::EventHandler* ConnectionRecieveEvent;
			//This fires when the connection is up
			Component::EventHandler* ConnectedEvent;
		private:
			//MEMBERS -------------------------------------------------------------
			//Window (for the message queue loop) for the non blocking socket
			HWND hwnd;
			//Separate thread for the window
			HANDLE thread;
			//Separate thread for the ping sending messages
			HANDLE pingThread;
			//Connection with the server
			SOCKET connection;
			//This is used so, Stop and message queue loop don't call CleanupConnection at the same time
			CRITICAL_SECTION csCleanup;
			//Is connection up?
			//volatile because it may be accessed by different threads.
			volatile bool connIsUp;
			//State, save the data/bytes that has been recieved.
			DataState state;

			//METHODS -------------------------------------------------------------
			//This is called when connection fails in the message queue loop and Stop()
			//It only closes both and disconnects socket
			void CleanupConnection();

			//Helper function: creates the window (hwnd)
			void CreateWindowHWND();
			//Initializes the socket and the connection.
			//It needs the hwnd (window)
			bool Connect();

			/* NOT Owner. To display the errors. */
			Debug::Debug* debug;
		};
	}
}

#endif