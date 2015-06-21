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
		struct DEBUG_LOGCOLOR{
			DEBUG_LOGCOLOR(){}
			enum Value{
				BLUE, RED, GREEN, YELLOW, WHITE
			};
		};
		
		class Debug{
		public:
			Debug(const char* path, bool isConsoleAvailable, DEBUG_LEVEL::Value debug_level, const bool _debug_log);
			~Debug();

			void init(Network::ServerConn* conn);
			//Restarts the connection
			void restart();
			void stop();

			/* We are going to use the macro instead. If we need to log to network but create a new macro */
			void __l(const char* str);
			void __l(const std::string& str);
			void __l(const char* str, DEBUG_LOGCOLOR::Value color);
			void __l(const std::string& str, DEBUG_LOGCOLOR::Value color);

			//e is to show errors.
			void e(const char* str);
			void e(const std::string& str);
			void setConsoleAvailable(bool isIt);
			//Test the connection
			void _test();

			//This is used for serverConn when the connection fails.
			//Because is it reduntant when the connection fails, it will try to send the log over the connection.
			void localL(const char* str);
		private:
			/* Owner */
			Log* log;
			/* Owner */
			Network::ServerConn* conn;

			const bool debug_log;
			bool consoleAvailable;
			bool noDebug;
			bool onlyFileDebug;
		};
	}
}
#endif