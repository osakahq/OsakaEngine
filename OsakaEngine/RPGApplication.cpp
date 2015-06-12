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
		RPGApplication::RPGApplication(Debug::DebugPTR& d, Engine::SDLLibPTR& sdl, Engine::IFileLoaderPTR& fileloader, const bool _show_fpscounter) 
			: EApplication(d, sdl, fileloader), show_fpscounter(_show_fpscounter){
			gsm = nullptr;
			assetm = nullptr;
			ruler = nullptr;
			counter = nullptr;
			gameDataParams = nullptr;
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
			gameDataParams->_delete(); gameDataParams = nullptr;
			
			scenefactory->_delete(); scenefactory = nullptr;
			factory->_delete(); factory = nullptr;
			rpgfactory->_delete(); rpgfactory = nullptr;
			loader->_delete(); loader = nullptr;
			//Managers
			assetm->_delete(); assetm = nullptr;
			texturem->_delete(); texturem = nullptr;
			fontm->_delete(); fontm = nullptr;
			soundm->_delete(); soundm = nullptr;

			gsm->_delete(); gsm = nullptr;

			ruler->_delete(); ruler = nullptr;
			timem->_delete(); timem = nullptr;
			counter->_delete(); counter = nullptr;
			
			//loadingscene = nullptr;
			initscene = nullptr;
		}
		void RPGApplication::Init(bool vsync, int timePerFrame, int maxUpdatesToCatchUp, GameSessionManagerPTR& gsm){
			EApplication::Init(vsync, timePerFrame, maxUpdatesToCatchUp);
			this->gsm = gsm;
			if( settings == nullptr || gameData == nullptr  || factory == nullptr || rpgfactory == nullptr || scenefactory == nullptr ||
				loader == nullptr || assetm == nullptr || ruler == nullptr || timem == nullptr || counter == nullptr || this->gsm == nullptr || gameDataParams == nullptr ||
				texturem == nullptr || fontm == nullptr || soundm == nullptr )
			{
				debug->e("[RPGApplication] Init failed.");
			}
		}

		void RPGApplication::CallLoad(std::string id){
			std::dynamic_pointer_cast<RPGScene>(scenes[id])->Load(rpgfactory);
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

		void RPGApplication::Run(const char* scene, Engine::ESceneArgsPTR& init_params){
			if( loadingscene_id.empty() || initscene == nullptr )
				throw std::exception("[RPGApplication] loadingscene is nullptr or initscene is nullptr");

			//We switch the init scene with the args that has the initial real scene
			InitSceneArgsPTR args = std::make_shared<InitSceneArgs>();
			args->scene = scene;
			args->init_args = init_params; //These params are passed to the real first scene
			this->Switch(initscene->GetId().c_str(), std::static_pointer_cast<Engine::ESceneArgs>(args));

			if( show_fpscounter ){ //constant
				counter->Start();
			}

			EApplication::Run();
		}

		void RPGApplication::FadeStackTransition(const char* scene, Engine::ESceneArgsPTR& params){
			LoadingArgsPTR args = std::make_shared<LoadingArgs>();
			args->scene = scene;
			args->send_params = params;
			args->type = TransitionType::FADE_STACK;
			Stack(loadingscene_id.c_str(), std::static_pointer_cast<Engine::ESceneArgs>(args));
		}
		void RPGApplication::FadeSwitchTransition(const char* scene, Engine::ESceneArgsPTR& params){
			LoadingArgsPTR args = std::make_shared<LoadingArgs>();
			args->scene = scene;
			args->send_params = params;
			args->type = TransitionType::FADE_SWITCH;
			Stack(loadingscene_id.c_str(), std::static_pointer_cast<Engine::ESceneArgs>(args));
		}
		void RPGApplication::LoadingStackTransition(const char* scene, Engine::ESceneArgsPTR& params){
			LoadingArgsPTR args = std::make_shared<LoadingArgs>();
			args->scene = scene;
			args->send_params = params;
			args->type = TransitionType::LOADING_STACK;
			Stack(loadingscene_id.c_str(), std::static_pointer_cast<Engine::ESceneArgs>(args));
		}

		void RPGApplication::SetLoadingScene(std::string loadingscene_id){
			this->loadingscene_id = loadingscene_id;
		}
		void RPGApplication::SetInitScene(InitScenePTR& scene){
			this->initscene = scene;
		}
		
		GameSessionManagerPTR RPGApplication::GetGameSessionManager(){
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