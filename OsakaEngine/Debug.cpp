#include "stdafx.h"
#include "ServerConn.h"
#include "Log.h"
//For forward declarations, you need to add them last
#include "ConsoleColors.h"
#include "Debug.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace Debug{

		Debug::Debug(const char* path, bool isConsoleAvailable, DEBUG_LEVEL::Value debug_level){
			consoleAvailable = isConsoleAvailable;
			log = std::make_shared<Log>(path);
			
			noDebug = false;
			onlyFileDebug = false;

			switch(debug_level){
			case DEBUG_LEVEL::CONSOLE: 
				/*do nothing*/ 
				break;
			case DEBUG_LEVEL::REMOTE:
				this->restart();
				break;
			case DEBUG_LEVEL::NONE:
				noDebug = true;
				break;
			case DEBUG_LEVEL::FILE:
				onlyFileDebug = true;
				break;
			}
		}
		Debug::~Debug(){
#ifdef _DEBUG
			_CHECKDELETE("Debug");
#endif
		}
		void Debug::_delete(){
			//~ServerConn() calls Stop(); so it may call `debug->l`
			conn->_delete(); conn = nullptr;
			log->_delete(); log = nullptr;
		}
		void Debug::init(Network::ServerConnPTR& conn){
			this->conn = conn;
		}
		void Debug::restart(){
			if( conn->isConnected() ){
				l("[Debug] Restart failed. Connection is on.");
				return;
			}
			//conn->Stop(); //Start calls Stop();
			conn->StartAndWaitForConnection();
		}
		void Debug::stop(){
			this->conn->Stop();
		}
		void Debug::setConsoleAvailable(bool isIt){
			consoleAvailable = isIt;
		}
		//TODO: Show message box if console is unavailable
		void Debug::e(const char* str){
			l(str);
			//SetForegroundWindow(GetConsoleWindow());
			std::wstring wstr;
			std::string temp = str;
			wstr.assign(temp.begin(), temp.end());
			MessageBox(NULL, wstr.c_str(), L"Debug - Exception", NULL);
			throw std::exception(str);
		}
		void Debug::e(std::string str){
			l(str.c_str());
			//SetForegroundWindow(GetConsoleWindow());
			std::wstring wstr;
			wstr.assign(str.begin(), str.end());
			MessageBox(NULL, wstr.c_str(), L"Debug - Exception", NULL);
			throw std::exception(str.c_str());
		}
		void Debug::l(const char* str, DEBUG_LOGCOLOR::Value color){
			switch(color){
			case DEBUG_LOGCOLOR::BLUE:
				std::cout << blue;
				break;
			case DEBUG_LOGCOLOR::RED:
				std::cout << red;
				break;
			case DEBUG_LOGCOLOR::GREEN:
				std::cout << green;
				break;
			case DEBUG_LOGCOLOR::YELLOW:
				std::cout << yellow;
				break;
			case DEBUG_LOGCOLOR::WHITE:
				std::cout << white;
				break;
			}
			l(str);
			std::cout << white;
		}
		void Debug::l(std::string str, DEBUG_LOGCOLOR::Value color){
			l(str.c_str(), color);
		}
		void Debug::l(std::string str){
			l(str.c_str());
		}
		void Debug::l(const char* str){
			if( noDebug )
				return;
			if( log == nullptr ){
				//This should never happen.
				throw std::exception("[Debug] log is null");
				return;
			}
			if( conn->isConnected() ){
				if( !conn->Send(str) ){
					if( consoleAvailable ){
						//log.consoleL("[Debug] Failed to send message to server");
						log->consoleL(str);
					}else{
						//log.fileL("[Debug] Failed to send message to server");
						log->fileL(str);
					}
				}
			}else{
				if( consoleAvailable && onlyFileDebug == false ){
					log->consoleL(str);
				}else{
					log->fileL(str);
				}
			}
		}
		void Debug::localL(const char* str){
			if( consoleAvailable && onlyFileDebug == false ){
				log->consoleL(str);
			}else{
				log->fileL(str);
			}
		}

		void Debug::_test(){
			/*Debug::Debug debug("log.txt");
			debug.init(true);
	
			char data[1024];
			int id = 0;

			bool outer_quit = false;
			bool quit = false;

			while(!outer_quit){
				printf("\n[s]tart [e]xit (inner loop [x] to exit): ");
				std::cin >> data;
				if( strcmp(data, "e") == 0 ){
					outer_quit = true;
				}else if( strcmp(data, "s") == 0 ){
					debug.restart();
					quit = false;
					while(!quit){
						printf("Send command to server (Exit press x): ");
						std::cin >> data;
						if( strcmp(data, "x") == 0 ){
							debug.stop();
							quit = true;
						}else if( strcmp(data, "t") == 0 ){
							debug.l("message1");
							debug.l("message23");
							debug.l("message23454545");
						}else if( strcmp(data, "a") == 0 ){
							char data1[1024];
							char data2[1024];
							char data3[1024];
							sprintf_s(data1, "sm-%d:%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d:em-%d", ++id, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, id);
							sprintf_s(data2, "sm-%d:%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d:em-%d", ++id, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, id);
							sprintf_s(data3, "sm-%d:%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d:em-%d", ++id, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, id);
							debug.l(data1);
							debug.l(data2);
							debug.l(data3);
						}else{
							debug.l(data);
						}
					}
				}
			}

			printf("\nExit. Press enter to continue...\n");
			getchar();getchar();*/
		}

	}
}