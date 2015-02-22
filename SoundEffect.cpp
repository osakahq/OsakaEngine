#include "stdafx.h"
#include "Debug.h"
#include "IFileLoader.h"
#include "Sound.h"
#include "SoundEffect.h"
namespace Osaka{
	namespace Engine{
		SoundEffect::SoundEffect(Debug::DebugPTR& debug, IFileLoaderPTR& fileloader) : Sound(debug, fileloader){
			effect = NULL;
		}
		SoundEffect::~SoundEffect(){
#ifdef _DEBUG
			_CHECKDELETE("SoundEffect");
#endif
			if( effect != NULL )
				Mix_FreeChunk(effect);
		}
		void SoundEffect::_delete(){
			Sound::_delete();
		}
		void SoundEffect::Load(const char* filename){
			if( effect != NULL ){
				debug->l("[SoundEffect] WARNING! Sound is already loaded: " + std::string(filename));
				return;
			}
			effect = fileloader->LoadWAV(filename);
		}
		void SoundEffect::Play(int times){
			Mix_PlayChannel(-1, effect, 0);
		}
	}
}