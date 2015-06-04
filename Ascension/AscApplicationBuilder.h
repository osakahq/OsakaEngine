 #include "stdafx.h"
#ifndef ASC_ASCAPPLICATIONBUILDER_H
#define ASC_ASCAPPLICATIONBUILDER_H
#include <RPGApplicationBuilder.h>

namespace Osaka{
	namespace Asc{

		class AscApplicationBuilder : public RPGLib::RPGApplicationBuilder{
		public:
			
		protected:

			RPGLib::RPGApplicationPTR CreateRPGApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader) override;
		};
		
	}
}
#endif