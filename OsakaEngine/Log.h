 #include "stdafx.h"

#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

namespace Osaka{
	namespace Debug{

		class Log{
		public:
			Log(const char* file);
			~Log();
			
			void fileL(const char* str);
			void consoleL(const char* str);
		private:
			std::shared_ptr<std::ofstream> file;
			std::string file_path;
			bool fileInit;
		};
	}
}
#endif