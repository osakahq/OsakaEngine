 #include "stdafx.h"

#ifndef ASC_ASCAPPLICATION_H
#define ASC_ASCAPPLICATION_H

#include "RPGApplication.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace Asc{

		class AscApplication : public RPGLib::RPGApplication{
		public:
			AscApplication(Debug::DebugPTR& d, Engine::SDLLibPTR& sdl, Engine::IFileLoaderPTR& fileloader);
			~AscApplication();
			void _delete();

			void Update();
		};
	}
}
#endif