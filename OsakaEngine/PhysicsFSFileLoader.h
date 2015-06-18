 #include "stdafx.h"

#ifndef ENGINE_PHYSICSFSFILELOADER_H
#define ENGINE_PHYSICSFSFILELOADER_H
#include "IFileLoader.h"
#include "osaka_forward.h"

namespace Osaka{
	
	namespace Engine{
		/* This is an interface */
		class PhysicsFSFileLoader : public IFileLoader{
		public:
			PhysicsFSFileLoader(Debug::Debug* debug, const char* filename);
			~PhysicsFSFileLoader();
			
			void AddFile(const char* filename);

			//All functions give away ownership
			Mix_Music* LoadMusic(const char* path) override;
			Mix_Chunk* LoadWAV(const char* path) override;
			SDL_Surface* LoadImageSurface(const char* path) override;
		private:
			/* NOT Owner */
			Debug::Debug* debug;
		};
	}
}

#endif
