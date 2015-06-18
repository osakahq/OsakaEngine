#include "stdafx.h"
#include "Debug.h"
#include "IFileLoader.h"
#include "Sound.h"
#include "SoundEffect.h"
namespace Osaka{
	namespace Engine{
		SoundEffect::SoundEffect(Debug::Debug* debug, IFileLoader* fileloader) : Sound(debug, fileloader){
			effect = NULL;
		}
		SoundEffect::~SoundEffect(){
#ifdef _DEBUG
			_CHECKDELETE("SoundEffect");
#endif
			if( effect != NULL )
				Mix_FreeChunk(effect);
		}
		
		void SoundEffect::Load(const char* filename){
			if( effect != NULL ){
				debug->e("[SoundEffect] WARNING! Sound is already loaded: " + std::string(filename));
				return;
			}
			effect = fileloader->LoadWAV(filename);
			if( effect == NULL ){
				debug->e("[SoundEffect] Load: effect is NULL");
			}
		}
		void SoundEffect::Play(int times){
#ifdef _DEBUG
			if( effect == NULL )
				debug->e("[SoundEffect] effect is NULL");
#endif
			Mix_PlayChannel(-1, effect, times);
		}
	}
}