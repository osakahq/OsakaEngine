 #include "stdafx.h"

#include "gamedata_include.h"
#include "SDLLib.h"
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
			sdl = nullptr;
			debug = nullptr;
			assetm = nullptr;
			fileloader = nullptr;
			app = nullptr;
			timem = nullptr;
		}
		void Factory::Check(){
			if( app == nullptr || sdl == nullptr || fileloader == nullptr || assetm == nullptr || timem == nullptr ){
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

		RPGLoadingScenePTR Factory::CreateRPGLoadingScene(const char* name){
#ifdef _DEBUG
			if( assetm == nullptr )
				throw std::exception("[Factory] assetm is nullptr");
#endif
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

			loadingscene->Init();

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

			scene->Init();

			return scene;
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
