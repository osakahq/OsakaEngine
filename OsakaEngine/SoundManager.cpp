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
		SoundManager::SoundManager(Factory* factory, Engine::SDLLib* sdl){
			this->factory = factory;
			this->sdl = sdl;
		}
		SoundManager::~SoundManager(){
			for(auto it = esounds.begin(); it != esounds.end(); ++it )
				delete it->second;
			esounds.clear();
			//sounds.clear();
			sounds = NULL;
			sdl = NULL;
			factory = NULL;
		}
		
		void SoundManager::SetSounds(unorderedmap_sound_data& sounds){
			this->sounds = &sounds;
		}
		void SoundManager::Init(){
			for( auto it = sounds->begin(); it!= sounds->end(); ++it ){
				this->esounds[it->first] = factory->CreateSound(*it->second);
			}
		}
		void SoundManager::LoadSound(const std::string& id){
			esounds.at(id)->Load(sounds->at(id)->filename.c_str());
		}

		void SoundManager::SetVolume(int volume){
			sdl->SetVolume(volume);
		}
		void SoundManager::SetMusicVolume(int volume){
			sdl->SetMusicVolume(volume);
		}


		void SoundManager::PlaySoundEffect(const std::string& id, int times){
			Engine::Sound* sound = this->esounds[std::string(id)];
			Engine::SoundEffect* effect = dynamic_cast<Engine::SoundEffect*>(sound);
			effect->Play(times);
		}

		void SoundManager::PlayMusic(const std::string& id){
			Engine::Sound* sound = this->esounds[std::string(id)];
			Engine::Music* music = dynamic_cast<Engine::Music*>(sound);
			sdl->PlayMusic(*music->GetRAWMixMusic());
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