 #include "stdafx.h"

#ifndef ASC_ASCAPPLICATIONCREATOR_H
#define ASC_ASCAPPLICATIONCREATOR_H

#include <RPGApplicationCreator.h>

namespace Osaka{
	namespace Asc{

		class AscApplicationCreator : public Utils::RPGApplicationCreator{
		public:
			/* Gives away ownership */
			RPGLib::RPGApplicationPTR CreateApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader);
		};
	}
}

#endif