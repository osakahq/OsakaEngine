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
		Factory::Factory(Debug::DebugPTR& debug){
			this->debug = debug;
		}
		Factory::~Factory(){
#ifdef _DEBUG
			_CHECKDELETE("Factory");
#endif				
		}
		void Factory::_delete(){
			sdl = nullptr;
			debug = nullptr;
			assetm = nullptr;
			fileloader = nullptr;
			app = nullptr;
			timem = nullptr;
			texturem = nullptr;
		}
		void Factory::Check(){
			if( app == nullptr || sdl == nullptr || fileloader == nullptr || assetm == nullptr || timem == nullptr || texturem == nullptr ){
				debug->e("[Factory] Init failed.");
			}
		}
		
		Engine::TexturePTR Factory::CreateTexture(){
#ifdef _DEBUG
			if( fileloader == nullptr )
				throw std::exception("[Factory] fileloader is nullptr");
#endif
			return std::make_shared<Engine::Texture>(*sdl->GetRAWSDLRenderer(), debug, fileloader);
		}
		Engine::SoundPTR Factory::CreateSound(sound_dataPTR& data){
#ifdef _DEBUG
			if( fileloader == nullptr )
				throw std::exception("[Factory] fileloader is nullptr");
#endif
			Engine::SoundPTR sound;
			if( data->type == SoundType::BGM ){
				sound = std::make_shared<Engine::Music>(debug, fileloader);
			}else{
				sound = std::make_shared<Engine::SoundEffect>(debug, fileloader);
			}
			return sound;
		}

		InitScenePTR Factory::CreateInitScene(){
			return std::make_shared<RPGLib::InitScene>(app);
		}

		TimerPTR Factory::CreateTimer(){
#ifdef _DEBUG
			if( timem == nullptr )
				throw std::exception("[Factory] timem is nullptr");
#endif
			TimerPTR timer = std::make_shared<Timer>(timem);
			return timer;
		}
	}
}
