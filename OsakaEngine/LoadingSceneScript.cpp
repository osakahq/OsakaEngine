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
		LoadingSceneScript::LoadingSceneScript(RPGApplicationPTR& app, AssetManagerPTR& assetm) 
			: SceneScript(app)
		{
			loadCompleted = false;
			this->assetm = assetm;

			fadelayer_id = "_fadelayer";
		}
		LoadingSceneScript::~LoadingSceneScript(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingSceneScript");
#endif			
		}
		void LoadingSceneScript::_delete(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingSceneScript_delete");
#endif	
			SceneScript::_delete();
			assetm = nullptr;
		}
		
		void LoadingSceneScript::LoadCompleted(){
			//This funcion is called by the loading thread inside GameLoader
			loadCompleted = true;
		}
		bool LoadingSceneScript::isLoadCompleted(){
			return loadCompleted;
		}

		void LoadingSceneScript::Ready(Engine::ESceneArgsPTR& params){
			loadCompleted = false;
			LoadingArgsPTR largs = std::dynamic_pointer_cast<LoadingArgs>(params);
			
			/* Using a raw pointer. There is no problem because the only way the anonymous function will be called is when this class calls `assetm->LoadScene(...)` */
			LoadingSceneScript* raw_loadingscene = this;
			assetm->LoadScene(largs->scene, [raw_loadingscene](){
				/* This anonymous function will be called inside AssetManager:ProcessLoad function (the other thread) */
				raw_loadingscene->LoadCompleted();
			});

			LoadingFadeLayerArgsPTR args = std::make_shared<LoadingFadeLayerArgs>();
			args->scene_id = largs->scene;
			args->scene_params = largs->send_params;
			args->type = largs->type;
			
			scene_parent->Stack(fadelayer_id, std::static_pointer_cast<LayerArgs>(args));
		}
	}
}