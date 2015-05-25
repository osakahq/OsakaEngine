 #include "stdafx.h"

#include "FPSCounter.h"
#include "ESceneArgs.h"
#include "EScene.h"
#include "Debug.h"
#include "Settings.h"
#include "GameData.h"
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
#include "RPGLoadingScene.h"

#include "IFileLoader.h"
#include "EApplication.h"
#include "RPGScene.h"
#include "RPGApplication.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGApplication::RPGApplication(Debug::DebugPTR& d, Engine::SDLLibPTR& sdl, Engine::IFileLoaderPTR& fileloader) : EApplication(d, sdl, fileloader){
			this->sessionm = nullptr;
			assetm = nullptr;
			ruler = nullptr;
			counter = nullptr;

		}

		RPGApplication::~RPGApplication(){
#ifdef _DEBUG
			_CHECKDELETE("RPGApplication");
#endif
		}
		void RPGApplication::_delete(){
			EApplication::_delete();
			settings->_delete(); settings = nullptr;
			gameData->_delete(); gameData = nullptr;
			
			factory->_delete(); factory = nullptr;
			rpgfactory->_delete(); rpgfactory = nullptr;
			loader->_delete(); loader = nullptr;
			assetm->_delete(); assetm = nullptr;
			sessionm->_delete(); sessionm = nullptr;

			ruler->_delete(); ruler = nullptr;
			timem->_delete(); timem = nullptr;
			counter->_delete(); counter = nullptr;
			
			loadingscene = nullptr;
			initscene = nullptr;
		}
		void RPGApplication::Init(bool vsync, int timePerFrame){
			EApplication::Init(vsync, timePerFrame);
			if( settings == nullptr || gameData == nullptr  || factory == nullptr || rpgfactory == nullptr || 
				loader == nullptr || assetm == nullptr || ruler == nullptr || timem == nullptr || counter == nullptr)
			{
				debug->e("[RPGApplication] Init failed.");
			}
		}

		void RPGApplication::Update(){
			EApplication::Update();
			/* Runs every update. */
			timem->UpdateTicks();

			
		}
		void RPGApplication::BeforePresent(){
			EApplication::BeforePresent();
			counter->BeforePresent();
		}

		void RPGApplication::RenderTime(Uint32 frame_ms){
			//This function is only called when _DEBUG
			counter->AfterPresent(frame_ms);
		}

		void RPGApplication::Run(const char* scene, Engine::ESceneArgsPTR& init_params){
			if( loadingscene == nullptr || initscene == nullptr )
				throw std::exception("[RPGApplication] loadingscene is nullptr or initscene is nullptr");

			counter->Start();

			//We switch the init scene with the args that has the initial real scene
			InitSceneArgsPTR args = std::make_shared<InitSceneArgs>();
			args->scene = scene;
			args->init_args = init_params; //These params are passed to the real first scene
			this->Switch(initscene->GetId().c_str(), std::static_pointer_cast<Engine::ESceneArgs>(args));

			EApplication::Run();
		}

		void RPGApplication::SetGameSessionManager(GameSessionManagerPTR initialGSM){
			this->sessionm = initialGSM;
		}
		
		void RPGApplication::SetLoadingScene(RPGLoadingScenePTR& scene){
			this->loadingscene = scene;
		}
		void RPGApplication::SetInitScene(InitScenePTR& scene){
			this->initscene = scene;
		}

		GameSessionManagerPTR RPGApplication::GetGameSessionManager(){
			//See RPGScene:Reset() function
			//resetScenes.push_back(scene.id);
			return sessionm;
		}

		void RPGApplication::FadeStackTransition(const char* scene, Engine::ESceneArgsPTR& params){
			loadingscene->StartTransition(scene, params, TransitionType::FADE_STACK);
		}
		void RPGApplication::FadeSwitchTransition(const char* scene, Engine::ESceneArgsPTR& params){
			loadingscene->StartTransition(scene, params, TransitionType::FADE_SWITCH);
		}
		void RPGApplication::LoadingStackTransition(const char* scene, Engine::ESceneArgsPTR& params){
			loadingscene->StartTransition(scene, params, TransitionType::LOADING_STACK);
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