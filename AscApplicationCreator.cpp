 #include "stdafx.h"

#include "Debug.h"
#include "SDLLib.h"
#include "IFileLoader.h"
#include "RPGApplication.h"
#include "AscApplication.h"

#include "ApplicationCreator.h"
#include "AscApplicationCreator.h"

namespace Osaka{
	namespace Asc{

		RPGLib::RPGApplicationPTR AscApplicationCreator::CreateApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader){
			return std::make_shared<Asc::AscApplication>(debug, sdl, fileloader);
		}
	}
}