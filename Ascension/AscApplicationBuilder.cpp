 #include "stdafx.h"

#include "AscApplication.h"
#include "AscApplicationBuilder.h"

namespace Osaka{
	namespace Asc{
		
		RPGLib::RPGApplicationPTR AscApplicationBuilder::CreateRPGApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader){
			return std::make_shared<AscApplication>(debug, sdl, fileloader);
		}

	}
}