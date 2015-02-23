 #include "stdafx.h"
#include "EventArgs.h"
#include "EScenePassParams.h"
#include "LoadingPassParams.h"
#include "Canvas.h"
#include "UserInterface.h"
#include "Script.h"
#include "EApplication.h"
#include "RPGApplication.h"
#include "RPGScene.h"
#include "AssetManager.h"
#include "RPGLoadingScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGLoadingScene::RPGLoadingScene(std::string id, RPGApplicationPTR& app, CanvasPTR& canvas, UserInterfacePTR& ui, ScriptPTR& script, AssetManagerPTR& assetm) 
			: RPGScene(id, app, canvas, ui, script)
		{
			loadCompleted = false;
			this->assetm = assetm;
		}
		RPGLoadingScene::~RPGLoadingScene(){
#ifdef _DEBUG
			_CHECKDELETE("RPGLoadingScene");
#endif			
		}
		void RPGLoadingScene::_delete(){
#ifdef _DEBUG
			_CHECKDELETE("RPGLoadingScene_delete");
#endif	
			RPGScene::_delete();
			assetm = nullptr;
		}
		void RPGLoadingScene::SceneTransition(const char* name, Engine::EScenePassParamsPTR& params, TransitionType::Value type){
			
			//WARNING: Using raw pointer
			RPGLoadingScene* raw_loadingscene = this;
			assetm->LoadScene(name, [raw_loadingscene](Component::EventArgs& e){
				/* This anonymous function will be called inside AssetManager:ProcessLoad function (the other thread) */
				raw_loadingscene->LoadCompleted();
			});

			//TODO: I'm not sure how to downgrade a PTR
			Engine::EScenePassParamsPTR loadingparams_ptr = std::make_shared<LoadingPassParams>();
			LoadingPassParams* loadingparams = (LoadingPassParams*)loadingparams_ptr.get();
			loadingparams->send_params = params;
			loadingparams->scene = name;
			loadingparams->type = type;

			//When calling app->switch(this->id), EApp will call this class.
			if( type == TransitionType::SWITCH ){
				app->Switch(this->id.c_str(), loadingparams_ptr);
			}else{
				app->Stack(this->id.c_str(), loadingparams_ptr);
			}
		}
		void RPGLoadingScene::LoadCompleted(){
			//This funcion is called by the loading thread inside GameLoader
			loadCompleted = true;
		}
		bool RPGLoadingScene::isLoadCompleted(){
			return loadCompleted;
		}
	}
}