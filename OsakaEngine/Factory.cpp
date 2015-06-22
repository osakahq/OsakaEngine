 #include "stdafx.h"

#include "gamedata_include.h"
#include "SDLLib.h"
#include "TimeManager.h"
#include "Timer.h"
#include "Sound.h"
#include "Music.h"
#include "SoundEffect.h"
#include "Texture.h"
#include "TextureManager.h"
#include "AssetManager.h"
#include "GameData.h"
#include "GameDataLoader.h"
#include "IFileLoader.h"
#include "RPGApplication.h"

#include "InitScene.h"

//---
#include "Debug.h"
#include "Factory.h"

namespace Osaka{
	namespace RPGLib{
		Factory::Factory(Debug::Debug* debug){
			this->debug = debug;

			sdl = NULL;
			this->debug = NULL;
			assetm = NULL;
			fileloader = NULL;
			app = NULL;
			timem = NULL;
			texturem = NULL;
		}
		Factory::~Factory(){
			sdl = NULL;
			debug = NULL;
			assetm = NULL;
			fileloader = NULL;
			app = NULL;
			timem = NULL;
			texturem = NULL;
		}
		
		void Factory::Check(){
			if( app == NULL || sdl == NULL || fileloader == NULL || assetm == NULL || timem == NULL || texturem == NULL ){
				debug->e("[Factory] Init failed.");
			}
		}
		
		Engine::Texture* Factory::CreateTexture(){
			if( fileloader == NULL )
				throw std::exception("[Factory] fileloader is nullptr");

			return new Engine::Texture(sdl->GetRAWSDLRenderer(), debug, fileloader);
		}
		Engine::Sound* Factory::CreateSound(sound_data& data){
			if( fileloader == NULL )
				throw std::exception("[Factory] fileloader is nullptr");

			Engine::Sound* sound;
			if( data.type == SoundType::BGM ){
				sound = new Engine::Music(debug, fileloader);
			}else{
				sound = new Engine::SoundEffect(debug, fileloader);
			}
			return sound;
		}

		InitScene* Factory::CreateInitScene(){
			return new RPGLib::InitScene(app);
		}

		Timer* Factory::CreateTimer(){
			if( timem == NULL )
				throw std::exception("[Factory] timem is nullptr");

			return new Timer(timem);
		}
	}
}
