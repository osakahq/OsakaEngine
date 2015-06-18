#include "stdafx.h"
#include "Log.h"

namespace Osaka{
	namespace Debug{
		Log::Log(const char* file){
			file_path = file;
			fileInit = false;
			this->file = std::make_shared<std::ofstream>();
		}
		Log::~Log(){
#ifdef _DEBUG
			_CHECKDELETE("Log");
#endif
			if( file->is_open() ){
				file->close();
			}
			file = nullptr;
		}
		
		void Log::consoleL(const char* str){
			printf("%s\n", str);
		}

		void Log::fileL(const char* str){
			if( !fileInit ){
				fileInit = true;
				file->open(file_path.c_str(), std::ios::out | std::ios::ate);
				(*file) << "-----------------------------------------------------------------------------------------------" << std::endl;
			}
			(*file) << str << std::endl;
		}

	}
}