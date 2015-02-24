 #include "stdafx.h"

#include "EScenePassParams.h"
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
#include "RPGLoadingScene.h"

#include "FPSCounter.h"
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

			firstUpdate = 0; //init
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
		}
		void RPGApplication::Init(bool vsync, int timePerFrame){
			EApplication::Init(vsync, timePerFrame);
			if( settings == nullptr || gameData == nullptr  || factory == nullptr || rpgfactory == nullptr || 
				loader == nullptr || assetm == nullptr || loadingscene == nullptr || ruler == nullptr || timem == nullptr || counter == nullptr)
			{
				debug->e("[RPGApplication] Init failed.");
			}
		}

		void RPGApplication::Update(){
			EApplication::Update();
			/* Runs every update. */
			timem->UpdateTicks();

			if( firstUpdate != 2 ){
				//Means it hasn't called the firstupdate section
				if( firstUpdate == 1 ){ //1 = first update(true)
					/* Basically, we are waiting for a full loop to end, and then we switch the first scene. Scenes should only be inside the loop */
					SwitchTransition(first_scene.c_str(), Engine::EmptyScenePassParamsPTR);
					firstUpdate = 2; //2 = first_update(false)

				}else if( firstUpdate == 0 ){//0 = initialized
					firstUpdate = 1; //1 = first update has passed
				}
			}
		}
		void RPGApplication::AfterDraw(){
			EApplication::AfterDraw();
			counter->EndOfFrame();
		}

		void RPGApplication::Run(const char* scene){
			first_scene = scene;
			EApplication::Run();
		}

		void RPGApplication::SetGameSessionManager(GameSessionManagerPTR initialGSM){
			this->sessionm = initialGSM;
		}
		
		void RPGApplication::SetLoadingScene(RPGLoadingScenePTR& scene){
			this->loadingscene = scene;
		}

		GameSessionManagerPTR RPGApplication::GetGameSessionManager(){
			//See RPGScene:Reset() function
			//resetScenes.push_back(scene.id);
			return sessionm;
		}

		void RPGApplication::SwitchTransition(const char* scene, Engine::EScenePassParamsPTR& params){
			loadingscene->SceneTransition(scene, params, TransitionType::SWITCH);
		}
		void RPGApplication::StackTransition(const char* scene, Engine::EScenePassParamsPTR& params){
			loadingscene->SceneTransition(scene, params, TransitionType::STACK);
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