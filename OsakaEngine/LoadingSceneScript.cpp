 #include "stdafx.h"
#include "Debug.h"
#include "LoadingArgs.h"

#include "LoadingFadeScript.h"
#include "RPGApplication.h"
#include "RPGScene.h"
#include "AssetManager.h"
#include "LoadingSceneScript.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		LoadingSceneScript::LoadingSceneScript(RPGApplication* app, AssetManager* assetm) 
			: SceneScript(app), fadelayer_id("_fadelayer")
		{
			loadCompleted = false;
			this->assetm = assetm;

		}
		LoadingSceneScript::~LoadingSceneScript(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingSceneScript");
#endif			
			assetm = NULL;
		}
		
		void LoadingSceneScript::LoadCompleted(){
			//This funcion is called by the loading thread inside GameLoader
			loadCompleted = true;
		}
		bool LoadingSceneScript::isLoadCompleted(){
			return loadCompleted;
		}

		void LoadingSceneScript::Ready(Engine::ESceneArgs& params){
			loadCompleted = false;
			LoadingArgs* largs = dynamic_cast<LoadingArgs*>(&params);
			
			/* Using a raw pointer. There is no problem because the only way the anonymous function will be called is when this class calls `assetm->LoadScene(...)` */
			LoadingSceneScript* raw_loadingscene = this;
			assetm->LoadScene(largs->scene, [raw_loadingscene](){
				/* This anonymous function will be called inside AssetManager:ProcessLoad function (the other thread) */
				raw_loadingscene->LoadCompleted();
			});

			LoadingFadeLayerArgs* args = new LoadingFadeLayerArgs();
			args->scene_id = largs->scene;
			args->scene_params = largs->send_params;
			args->type = largs->type;
			
			scene_parent->Stack(fadelayer_id, *args);
			delete args;
		}
	}
}