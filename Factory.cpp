 #include "stdafx.h"

#include "gamedata_include.h"
#include "TimeManager.h"
#include "Timer.h"
#include "Sound.h"
#include "Music.h"
#include "SoundEffect.h"
#include "Texture.h"
#include "AssetManager.h"
#include "GameData.h"
#include "GameDataLoader.h"
#include "IFileLoader.h"
#include "RPGApplication.h"
//----
#include "RPGScene.h"
#include "Canvas.h"
#include "Script.h"
#include "UserInterface.h"

#include "LoadingScript.h"
#include "LoadingCanvas.h"
#include "LoadingUI.h"

#include "PlaybackIntroCanvas.h"
#include "PlaybackIntroScript.h"
#include "PlaybackIntroUI.h"

#include "RPGLoadingScene.h"
//---
#include "Debug.h"
#include "Factory.h"
#include "osaka_forward.h"

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
			debug = nullptr;
			assetm = nullptr;
			fileloader = nullptr;
			app = nullptr;
			timem = nullptr;
		}
		void Factory::Init(){
			if( app == nullptr || renderer == nullptr || fileloader == nullptr || assetm == nullptr || timem == nullptr ){
				debug->e("[Factory] Init failed.");
			}
		}
		GameDataPTR Factory::CreateGameData(){
			return std::make_shared<GameData>();
		}
		Engine::TexturePTR Factory::CreateTexture(){
			return std::make_shared<Engine::Texture>(*renderer, debug, fileloader);
		}
		Engine::SoundPTR Factory::CreateSound(sound_dataPTR& data){
			Engine::SoundPTR sound;
			if( data->type == SoundType::BGM ){
				sound = std::make_shared<Engine::Music>(debug, fileloader);
			}else{
				sound = std::make_shared<Engine::SoundEffect>(debug, fileloader);
			}
			return sound;
		}

		RPGLoadingScenePTR Factory::CreateRPGLoadingScene(const char* name){
			LoadingCanvasPTR canvas = std::make_shared<LoadingCanvas>(app);
			LoadingUIPTR ui = std::make_shared<LoadingUI>(app);
			LoadingScriptPTR script = std::make_shared<LoadingScript>(app);
			
			//TODO: I had to use shared_ptr because make_shared does not accept more than 5 parameters...
			RPGLoadingScenePTR loadingscene = std::shared_ptr<RPGLoadingScene>(
				new RPGLoadingScene(name, app, 
					std::static_pointer_cast<Canvas>(canvas), 
					std::static_pointer_cast<UserInterface>(ui), 
					std::static_pointer_cast<Script>(script), this->assetm)
			);

			script->Init(loadingscene, canvas, ui);
			canvas->Init(CreateTimer());
			ui->Init();

			return loadingscene;
		}

		RPGScenePTR Factory::CreatePlaybackIntroScene(const char* name){
			PlaybackIntroCanvasPTR canvas = std::make_shared<PlaybackIntroCanvas>(app);
			PlaybackIntroUIPTR ui = std::make_shared<PlaybackIntroUI>(app);
			PlaybackIntroScriptPTR script = std::make_shared<PlaybackIntroScript>(app);

			RPGScenePTR scene = std::shared_ptr<RPGScene>(
				new RPGScene(name, app, 
					std::static_pointer_cast<Canvas>(canvas), 
					std::static_pointer_cast<UserInterface>(ui), 
					std::static_pointer_cast<Script>(script)
				)
			);

			script->Init(canvas, ui);
			canvas->Init();
			ui->Init();

			return scene;
		}

		TimerPTR Factory::CreateTimer(){
			TimerPTR timer = std::make_shared<Timer>(timem);
			return timer;
		}
	}
}
