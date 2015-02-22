 #include "stdafx.h"

#ifndef DEBUG_DEBUG_H
#define DEBUG_DEBUG_H
#include "osaka_forward.h"
namespace Osaka{
	namespace Debug{
		struct DEBUG_LEVEL{
			DEBUG_LEVEL(){}
			enum Value{
				CONSOLE, FILE, NONE, REMOTE
			};
		};
		
		class Debug{
		public:
			Debug(const char* path, bool isConsoleAvailable, DEBUG_LEVEL::Value debug_level);
			~Debug();
			void _delete();
			void init(Network::ServerConnPTR& conn);
			//Restarts the connection
			void restart();
			void stop();
			void l(const char* str);
			void l(std::string str);
			//e is to show errors.
			void e(const char* str);
			void e(std::string str);
			void setConsoleAvailable(bool isIt);
			//Test the connection
			void _test();

			//This is used for serverConn when the connection fails.
			//Because is it reduntant when the connection fails, it will try to send the log over the connection.
			void localL(const char* str);
		private:
			/* Owner */
			LogPTR log;
			/* Owner */
			Network::ServerConnPTR conn;

			bool consoleAvailable;
			bool noDebug;
			bool onlyFileDebug;
		};
	}
}
#endif