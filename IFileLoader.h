 #include "stdafx.h"

#ifndef ENGINE_FILELOADER_H
#define ENGINE_FILELOADER_H

namespace Osaka{
	namespace Engine{
		/* This is an interface */
		class IFileLoader{
		public:
			virtual ~IFileLoader(){}
			virtual void _delete() = 0;
			//All functions give away ownership
			virtual Mix_Music* LoadMusic(const char* path)=0;
			virtual Mix_Chunk* LoadWAV(const char* path)=0;
			virtual SDL_Surface* LoadImageSurface(const char* path)=0;
		private:
		};
	}
}

#endif
