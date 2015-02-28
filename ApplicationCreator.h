 #include "stdafx.h"

#ifndef UTIL_APPLICATIONCREATOR_H
#define UTIL_APPLICATIONCREATOR_H

#include "osaka_forward.h"

namespace Osaka{
	namespace Utils{

		class ApplicationCreator{
		public:
			/* Gives away ownership */
			virtual RPGLib::RPGApplicationPTR CreateApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader);
		};
	}
}

#endif