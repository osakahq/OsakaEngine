 #include "stdafx.h"
#include "Debug.h"
#include "IFileLoader.h"
#include "Sound.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace Engine{
		Sound::Sound(Debug::DebugPTR& debug, IFileLoaderPTR& fileloader){
			this->debug = debug;
			this->fileloader = fileloader;
		}
		Sound::~Sound(){
#ifdef _DEBUG
			_CHECKDELETE("Sound");
#endif			 
		}
		void Sound::_delete(){
			debug = nullptr;
			fileloader = nullptr;
		}
	}
}