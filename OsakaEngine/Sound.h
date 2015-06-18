 #include "stdafx.h"
#ifndef ENGINE_SOUND_H
#define ENGINE_SOUND_H
#include "osaka_forward.h"

namespace Osaka{
	namespace Engine{
		
		class Sound {
		public:
			Sound(Debug::Debug* debug, IFileLoader* fileloader);
			virtual ~Sound();
			virtual void Load(const char* filename) = 0;
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			IFileLoader* fileloader;
			/* NOT Owner */
			Debug::Debug* debug;
		};
	}
}
#endif