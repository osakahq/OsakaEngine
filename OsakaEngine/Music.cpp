 #include "stdafx.h"
#include "Debug.h"
#include "IFileLoader.h"
#include "Sound.h"
#include "Music.h"

namespace Osaka{
	namespace Engine{
		Music::Music(Debug::DebugPTR& debug, IFileLoaderPTR& fileloader) : Sound(debug, fileloader){
			music = NULL;
		}
		Music::~Music(){
#ifdef _DEBUG
			_CHECKDELETE("Music");
#endif
			if( music != NULL )
				Mix_FreeMusic(music);
			music = NULL;
		}
		void Music::_delete(){
			Sound::_delete();
		}
		Mix_Music* Music::GetRAWMixMusic(){
			if( music == NULL )
				debug->e("[Music] music is NULL");
			return music;
		}
		void Music::Load(const char* filename){
			if( music != NULL ){
				debug->e("[Music] WARNING! Sound is already loaded: " + std::string(filename));
				return;
			}
			music = fileloader->LoadMusic(filename);
			if( music == NULL ){
				debug->e("[Music] Load: music is NULL");
			}
		}
		
	}
}