 #include "stdafx.h"
#ifndef ENGINE_MUSIC_H
#define ENGINE_MUSIC_H
#include "Sound.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace Engine{
		
		class Music : public Sound {
		public:
			Music(Debug::DebugPTR& debug, IFileLoaderPTR & fileloader);
			~Music();
			void _delete();
			/* Owner */
			Mix_Music* music;

			void Load(const char* filename);
		/* ----------------------------------------------------------------------------------- */
		private:
			
		};
	}
}
#endif