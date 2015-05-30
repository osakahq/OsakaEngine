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
#include "Layer.h"
#include "Canvas.h"
#include "Script.h"
#include "UserInterface.h"

#include "LoadingSceneScript.h"
#include "LoadingFadeScript.h"
#include "LoadingFadeCanvas.h"

#include "PlaybackIntroSceneScript.h"
#include "PlaybackIntroCanvas.h"
#include "PlaybackIntroScript.h"


#include "InitScene.h"

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

		InitScenePTR Factory::CreateInitScene(){
			return std::make_shared<RPGLib::InitScene>(app);
		}

		RPGScenePTR Factory::CreateLoadingScene(const char* name){
#ifdef _DEBUG
			if( assetm == nullptr )
				throw std::exception("[Factory] assetm is nullptr");
#endif
			LoadingSceneScriptPTR mainscript = std::make_shared<LoadingSceneScript>(app, assetm);
			RPGScenePTR loadingscene = std::make_shared<RPGScene>(name, std::static_pointer_cast<SceneScript>(mainscript));
			mainscript->Init("fadelayer", loadingscene);

			LoadingFadeCanvasPTR canvas = std::make_shared<LoadingFadeCanvas>(app->sdl->GetRAWSDLRenderer(), app->ruler, CreateTimer());
			LoadingFadeScriptPTR script = std::make_shared<LoadingFadeScript>(app, loadingscene, canvas, mainscript);
			UserInterfacePTR ui = CreateDummyUI();
			LayerPTR layer = std::make_shared<Layer>("fadelayer", std::static_pointer_cast<Script>(script), std::static_pointer_cast<Canvas>(canvas), ui);
			layer->Init(app);
			
			script->Init(layer);
			canvas->Init(layer);
			ui->Init(layer);
			
			loadingscene->Add(layer);

			return loadingscene;
		}

		RPGScenePTR Factory::CreatePlaybackIntroScene(const char* name){

			PlaybackIntroSceneScriptPTR mainscript = std::make_shared<PlaybackIntroSceneScript>(app);
			RPGScenePTR scene = std::make_shared<RPGScene>(name, std::static_pointer_cast<SceneScript>(mainscript));
			mainscript->Init("layer1", scene);

			PlaybackIntroCanvasPTR canvas = std::make_shared<PlaybackIntroCanvas>(app->sdl->GetRAWSDLRenderer(), app->ruler);
			PlaybackIntroScriptPTR script = std::make_shared<PlaybackIntroScript>(app, scene, canvas, mainscript);
			UserInterfacePTR ui = CreateDummyUI();

			LayerPTR layer = std::make_shared<Layer>("layer1", std::static_pointer_cast<Script>(script), std::static_pointer_cast<Canvas>(canvas), ui);
			layer->Init(app);

			script->Init(layer);
			canvas->Init(layer);
			ui->Init(layer);

			scene->Add(layer);

			return scene;
		}

		UserInterfacePTR Factory::CreateDummyUI(){
			UserInterfacePTR ui = std::make_shared<UserInterface>(app->sdl->GetRAWSDLRenderer());
			return ui;
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
