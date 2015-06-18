 #include "stdafx.h"
#include "Debug.h"
#include "IFileLoader.h"
#include "Sound.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace Engine{
		Sound::Sound(Debug::Debug* debug, IFileLoader* fileloader){
			this->debug = debug;
			this->fileloader = fileloader;
		}
		Sound::~Sound(){
#ifdef _DEBUG
			_CHECKDELETE("Sound");
#endif			 
			debug = NULL;
			fileloader = NULL;
		}
		
	}
}