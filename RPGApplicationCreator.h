 #include "stdafx.h"

#ifndef UTIL_RPGAPPLICATIONCREATOR_H
#define UTIL_RPGAPPLICATIONCREATOR_H

#include "osaka_forward.h"

namespace Osaka{
	namespace Utils{

		/* This class exists because you can't dynamically create a class from text in C++.
		 * TODO: Maybe create a factory that creates all other classes if you need them to extend them */
		class RPGApplicationCreator{
		public:
			/* Gives away ownership */
			virtual RPGLib::RPGApplicationPTR CreateApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader);
		};
	}
}

#endif