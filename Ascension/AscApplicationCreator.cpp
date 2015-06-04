 #include "stdafx.h"

#include "OsakaEngine\Debug.h"
#include "OsakaEngine\SDLLib.h"
#include "OsakaEngine\IFileLoader.h"
#include "OsakaEngine\RPGApplication.h"
#include "AscApplication.h"

#include "AscApplicationCreator.h"

namespace Osaka{
	namespace Asc{

		RPGLib::RPGApplicationPTR AscApplicationCreator::CreateApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader){
			return std::make_shared<Asc::AscApplication>(debug, sdl, fileloader);
		}
	}
}