 #include "stdafx.h"
#include "Debug.h"
#include "SDLLib.h"
#include "IFileLoader.h"
#include "RPGApplication.h"
#include "RPGApplicationCreator.h"

namespace Osaka{
	namespace Utils{

		RPGLib::RPGApplicationPTR RPGApplicationCreator::CreateApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader){
			return std::make_shared<RPGLib::RPGApplication>(debug, sdl, fileloader);
		}
	}
}