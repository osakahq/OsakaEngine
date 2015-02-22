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

			loadingscene = nullptr;
		}
		void RPGApplication::Init(){
			EApplication::Init();
			if( settings == nullptr || gameData == nullptr  || factory == nullptr || rpgfactory == nullptr || 
				loader == nullptr || assetm == nullptr || loadingscene == nullptr || ruler == nullptr || timem == nullptr )
			{
				debug->e("[RPGApplication] Init failed.");
			}
		}

		void RPGApplication::Update(){
			EApplication::Update();
			/* Runs every update. */
			timem->UpdateTicks();
		}
		void RPGApplication::Run(const char* scene){
			SwitchTransition(scene, Engine::EmptyScenePassParamsPTR);
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