 #include "stdafx.h"
#include "DefaultFileLoader.h"
namespace Osaka{
	namespace Engine{
		DefaultFileLoader::~DefaultFileLoader(){
#ifdef _DEBUG
			_CHECKDELETE("DefaultFileLoader");
#endif
		}
		void DefaultFileLoader::_delete(){

		}
		Mix_Music* DefaultFileLoader::LoadMusic(const char* path){
			return Mix_LoadMUS(path);
		}
		Mix_Chunk* DefaultFileLoader::LoadWAV(const char* path){
			return Mix_LoadWAV(path);
		}
		SDL_Surface* DefaultFileLoader::LoadImageSurface(const char* path){
			return IMG_Load(path);
		}
	}
}