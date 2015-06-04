 #include "stdafx.h"

#include "OsakaEngine\Debug.h"
#include "OsakaEngine\SDLLib.h"
#include "OsakaEngine\RPGApplication.h"
#include "AscApplication.h"

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
