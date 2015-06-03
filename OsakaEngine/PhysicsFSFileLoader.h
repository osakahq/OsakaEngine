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
			PhysicsFSFileLoader(Debug::DebugPTR& debug, const char* filename);
			~PhysicsFSFileLoader();
			void _delete();
			void AddFile(const char* filename);

			//All functions give away ownership
			Mix_Music* LoadMusic(const char* path);
			Mix_Chunk* LoadWAV(const char* path);
			SDL_Surface* LoadImageSurface(const char* path);
		private:
			/* NOT Owner */
			Debug::DebugPTR debug;
		};
	}
}

#endif
