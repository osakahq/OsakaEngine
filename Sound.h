 #include "stdafx.h"
#ifndef ENGINE_SOUND_H
#define ENGINE_SOUND_H
#include "osaka_forward.h"

namespace Osaka{
	namespace Engine{
		
		class Sound {
		public:
			Sound(Debug::DebugPTR& debug, IFileLoaderPTR& fileloader);
			virtual ~Sound();
			virtual void _delete();
			virtual void Load(const char* filename) = 0;
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			IFileLoaderPTR fileloader;
			/* NOT Owner */
			Debug::DebugPTR debug;
		};
	}
}
#endif