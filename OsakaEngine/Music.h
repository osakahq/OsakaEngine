 #include "stdafx.h"
#ifndef ENGINE_MUSIC_H
#define ENGINE_MUSIC_H
#include "Sound.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace Engine{
		
		class Music : public Sound {
		public:
			Music(Debug::Debug* debug, IFileLoader* fileloader);
			~Music();
			
			void Load(const char* filename) override;

			Mix_Music* GetRAWMixMusic();
		/* ----------------------------------------------------------------------------------- */
		private:
			/* Owner */
			Mix_Music* music;
		};
	}
}
#endif