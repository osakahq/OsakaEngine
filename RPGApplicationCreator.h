 #include "stdafx.h"

#ifndef UTIL_APPLICATIONCREATOR_H
#define UTIL_APPLICATIONCREATOR_H

#include "osaka_forward.h"

namespace Osaka{
	namespace Utils{

		/* This class exists because you can't dynamically create a class from text in C++.
		 * TODO: Maybe create a factory that creates all other classes if you need them to extend them */
		class ApplicationCreator{
		public:
			/* Gives away ownership */
			virtual RPGLib::RPGApplicationPTR CreateApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader);
		};
	}
}

#endif