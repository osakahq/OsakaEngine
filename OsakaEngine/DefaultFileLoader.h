 #include "stdafx.h"

#ifndef ENGINE_DEFAULTFILELOADER_H
#define ENGINE_DEFAULTFILELOADER_H
#include "IFileLoader.h"
namespace Osaka{
	namespace Engine{
		/* This is an interface */
		class DefaultFileLoader : public IFileLoader{
		public:
			~DefaultFileLoader();
			void _delete();
			//All functions give away ownership
			Mix_Music* LoadMusic(const char* path);
			Mix_Chunk* LoadWAV(const char* path);
			SDL_Surface* LoadImageSurface(const char* path);
		private:
		};
	}
}

#endif
