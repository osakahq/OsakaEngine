 #include "stdafx.h"

#ifndef ASC_ASCAPPLICATIONCREATOR_H
#define ASC_ASCAPPLICATIONCREATOR_H

#include "OsakaEngine\RPGApplicationCreator.h"
#include "OsakaEngine\osaka_forward.h"

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