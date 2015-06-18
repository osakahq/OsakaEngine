 #include "stdafx.h"
#include "EScene.h"
#include "Debug.h"
#include "RPGApplication.h"
#include "InitScene.h"
#include "InitSceneArgs.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		InitScene::InitScene(RPGApplication* app){
			this->app = app;
			callTransition = true;
		}
		InitScene::~InitScene(){
#ifdef _DEBUG
			_CHECKDELETE("InitScene");
#endif		
			app = NULL;
			init_args = nullptr;
		}
		
		std::string InitScene::GetId(){
			return std::string("__rpglib_initscene");
		}
		
		void InitScene::ReadyShow(Engine::ESceneArgs& params){
			printf("[InitScene] ReadyShow\n");
			InitSceneArgs* args = dynamic_cast<InitSceneArgs*>(&params);
			app->debug->l("[InitScene] Scene: " + args->scene);
			scene = args->scene;
			init_args = args->init_args;
		}
		
		void InitScene::Update(){
			if( callTransition ){
				printf("[InitScene] Update -> callTransition\n");
				//Switch will make this scene go out of the loop.
				app->FadeSwitchTransition(scene, init_args);
				init_args = nullptr;
				callTransition = false;
			}
		}
		
		void InitScene::Start(){};
		void InitScene::Enter(){};
		void InitScene::Load(){};
		void InitScene::Unload() {};
		void InitScene::Exit() {};
		void InitScene::ReadyStandBy(Engine::ESceneArgs& params) {};
		void InitScene::StandBy() {};
		void InitScene::Focus() {};
		void InitScene::Draw() {};
		void InitScene::End() {};
	}
}