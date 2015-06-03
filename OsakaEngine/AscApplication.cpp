 #include "stdafx.h"

#include "Debug.h"
#include "SDLLib.h"
#include "RPGApplication.h"
#include "AscApplication.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace Asc{
		using namespace RPGLib;
		AscApplication::AscApplication(Debug::DebugPTR& d, Engine::SDLLibPTR& sdl, Engine::IFileLoaderPTR& fileloader) : RPGApplication(d, sdl, fileloader){

		}
		AscApplication::~AscApplication(){
#ifdef _DEBUG
			_CHECKDELETE("AscApplication");
#endif
		}
		void AscApplication::_delete(){
			RPGApplication::_delete();
		}

		void AscApplication::Update(){
			RPGApplication::Update();
		}
	}
}
