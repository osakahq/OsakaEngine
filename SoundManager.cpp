 #include "stdafx.h"
#include "gamedata_include.h"
#include "SDLLib.h"
#include "Sound.h"
#include "SoundEffect.h"
#include "Music.h"
#include "Factory.h"
#include "SoundManager.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		SoundManager::SoundManager(FactoryPTR& factory, Engine::SDLLibPTR& sdl){
			this->factory = factory;
			this->sdl = sdl;
		}
		SoundManager::~SoundManager(){
			
		}
		void SoundManager::_delete(){
			for(auto it = esounds.begin(); it != esounds.end(); ++it )
				it->second->_delete();
			esounds.clear();
			sounds = nullptr;
			sdl = nullptr;
			factory = nullptr;
		}
		void SoundManager::SetSounds(unorderedmap_sound_dataPTR& sounds){
			this->sounds = sounds;
			Engine::SoundPTR sound;
			for( auto it = sounds->begin(); it!= sounds->end(); ++it ){
				sound = factory->CreateSound(it->second);
				//sound->Load((*it->second).filename.c_str());
				this->esounds[it->first] = sound;
			}

		}
		void SoundManager::LoadSound(const std::string id){
			esounds.at(id)->Load(sounds->at(id)->filename.c_str());
		}

		void SoundManager::SetVolume(int volume){
			sdl->SetVolume(volume);
		}
		void SoundManager::SetMusicVolume(int volume){
			sdl->SetMusicVolume(volume);
		}


		void SoundManager::PlaySoundEffect(std::string id, int times){
			//TODO: I'm not sure how to upcast a shared_ptr
			Engine::SoundPTR sound = this->esounds[std::string(id)];
			Engine::SoundEffect* effect = (Engine::SoundEffect*)sound.get();
			effect->Play(times);
		}

		void SoundManager::PlayMusic(std::string id){
			//TODO: I'm not sure how to upcast a shared_ptr
			Engine::SoundPTR sound = this->esounds[std::string(id)];
			Engine::Music* music = (Engine::Music*)sound.get();
			sdl->PlayMusic(*music->music);
		}
		void SoundManager::PauseMusic(){
			sdl->PauseMusic();
		}
		void SoundManager::ResumeMusic(){
			sdl->ResumeMusic();
		}
		void SoundManager::StopMusic(){
			sdl->StopMusic();
		}
		void SoundManager::StopMusicFadeOut(int ms){
			sdl->StopMusicFadeOut(ms);
		}
	}
}