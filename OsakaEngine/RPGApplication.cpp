 #include "stdafx.h"

#include "SceneFactory.h"
#include "FPSCounter.h"
#include "ESceneArgs.h"
#include "EScene.h"
#include "Debug.h"
#include "Settings.h"
#include "GameData.h"
#include "GameDataParams.h"
#include "Ruler.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "Factory.h"
#include "RPGFactory.h"
#include "GameDataLoader.h"
#include "AssetManager.h"
#include "TimeManager.h"
#include "GameSessionManager.h"
#include "InitScene.h"
#include "InitSceneArgs.h"
#include "LoadingArgs.h"

#include "IFileLoader.h"
#include "EApplication.h"
#include "RPGScene.h"
#include "RPGApplication.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGApplication::RPGApplication(Debug::Debug* d, Engine::SDLLib* sdl, Engine::IFileLoader* fileloader, const bool _show_fpscounter) 
			: EApplication(d, sdl, fileloader), show_fpscounter(_show_fpscounter){

			settings = NULL;
			gameData = NULL;
			gameDataParams = NULL;
			
			scenefactory = NULL;
			factory = NULL;
			rpgfactory = NULL;
			loader = NULL;
			
			assetm = NULL;
			texturem = NULL;
			fontm = NULL;
			soundm = NULL;

			gsm = NULL;

			ruler = NULL;
			timem = NULL;
			counter = NULL;
			initscene = NULL;

			args = new LoadingArgs();
		}

		RPGApplication::~RPGApplication(){
#ifdef _DEBUG
			_CHECKDELETE("RPGApplication");
#endif
			delete settings; settings = NULL;
			delete gameData; gameData = NULL;
			delete gameDataParams; gameDataParams = NULL;
			
			delete scenefactory; scenefactory = NULL;
			delete factory; factory = NULL;
			delete rpgfactory; rpgfactory = NULL;
			delete loader; loader = NULL;
			//Managers
			delete assetm; assetm = NULL;
			delete texturem; texturem = NULL;
			delete fontm; fontm = NULL;
			delete soundm; soundm = NULL;

			delete gsm; gsm = NULL;

			delete ruler; ruler = NULL;
			delete timem; timem = NULL;
			delete counter; counter = NULL;

			delete args; args = NULL;
			//loadingscene = nullptr;
			initscene = NULL;
		}
		
		void RPGApplication::Init(bool vsync, int timePerFrame, int maxUpdatesToCatchUp, GameSessionManager* gsm){
			EApplication::Init(vsync, timePerFrame, maxUpdatesToCatchUp);
			this->gsm = gsm;
			if( settings == NULL || gameData == NULL  || factory == NULL || rpgfactory == NULL || scenefactory == NULL ||
				loader == NULL || assetm == NULL || ruler == NULL || timem == NULL || counter == NULL || this->gsm == NULL || gameDataParams == NULL ||
				texturem == NULL || fontm == NULL || soundm == NULL )
			{
				debug->e("[RPGApplication] Init failed.");
			}
		}

		void RPGApplication::CallLoad(const std::string& id){
			dynamic_cast<RPGScene*>(raw_scenes[id])->Load(*rpgfactory);
		}

		void RPGApplication::Update(const Uint32 delta){
			timem->Update(delta);
		}
	
		void RPGApplication::BeforePresent(){
			//EApplication::BeforePresent();
			if( show_fpscounter ){ //constant
				counter->BeforePresent();
			}
		}

		void RPGApplication::AfterPresent(const Uint32 started){
			//This function is always called.
			if( show_fpscounter ){ //constant
				counter->AfterPresent(started);
			}
		}

		void RPGApplication::Run(const std::string& scene, Engine::ESceneArgsPTR& init_params){
			if( loadingscene_id.empty() || initscene == NULL )
				throw std::exception("[RPGApplication] loadingscene is nullptr or initscene is nullptr");

			//We switch the init scene with the args that has the initial real scene
			InitSceneArgs* args = new InitSceneArgs();
			args->scene = scene;
			args->init_args = init_params; //These params are passed to the real first scene
			this->Switch(initscene->GetId(), *args);
			delete args;

			if( show_fpscounter ){ //constant
				counter->Start();
			}

			EApplication::Run();
		}
		void RPGApplication::End(){
			assetm->End(); //Unloads the loaded scenes
		}
		void RPGApplication::FadeStackTransition(const std::string& scene, const Engine::ESceneArgsPTR& params){
			LOG("[RPGApplication] FadeStackTransition\n");
			args->scene = scene;
			args->send_params = params;
			args->type = TransitionType::FADE_STACK;
			Stack(loadingscene_id, *args);

			args->send_params = nullptr;
		}
		void RPGApplication::FadeSwitchTransition(const std::string& scene, const Engine::ESceneArgsPTR& params){
			LOG("[RPGApplication] FadeSwitchTransition\n");
			args->scene = scene;
			args->send_params = params;
			args->type = TransitionType::FADE_SWITCH;
			Stack(loadingscene_id, *args);

			args->send_params = nullptr;
		}
		void RPGApplication::LoadingStackTransition(const std::string& scene, const Engine::ESceneArgsPTR& params){
			LOG("[RPGApplication] LoadingStackTransition\n");
			args->scene = scene;
			args->send_params = params;
			args->type = TransitionType::LOADING_STACK;
			Stack(loadingscene_id, *args);

			args->send_params = nullptr;
		}

		void RPGApplication::SetLoadingScene(const std::string& loadingscene_id){
			this->loadingscene_id = loadingscene_id;
		}
		void RPGApplication::SetInitScene(InitScene* scene){
			this->initscene = scene;
		}
		
		GameSessionManager* RPGApplication::GetGameSessionManager(){
			//See RPGScene:Reset() function
			//resetScenes.push_back(scene.id);
			return gsm;
		}
		void RPGApplication::SaveGame(const char* filename){

		}
		void RPGApplication::LoadGame(const char* filename){
			//foreach scene in scenes -> scene->Reset();
		}
		void RPGApplication::ExitGame(const char* scene){
			//foreach scene in scenes -> scene->Reset();
		}
	}
}