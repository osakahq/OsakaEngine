 #include "stdafx.h"

#ifndef ASC_ASCAPPLICATIONCREATOR_H
#define ASC_ASCAPPLICATIONCREATOR_H

#include "ApplicationCreator.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace Asc{

		class AscApplicationCreator : public Utils::ApplicationCreator{
		public:
			/* Gives away ownership */
			RPGLib::RPGApplicationPTR CreateApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader);
		};
	}
}

#endif