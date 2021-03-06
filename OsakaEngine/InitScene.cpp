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
			app = NULL;
			init_args = nullptr;
		}
		
		std::string InitScene::GetId(){
			return std::string("__rpglib_initscene");
		}
		
		void InitScene::ReadyShow(Engine::ESceneArgs& params){
			LOG("[InitScene] ReadyShow\n");
			InitSceneArgs* args = dynamic_cast<InitSceneArgs*>(&params);
			LOG("[InitScene] Scene: %s\n", args->scene.c_str());
			scene = args->scene;
			init_args = args->init_args;
		}
		
		void InitScene::Update(Engine::keyboard_state& state){
			if( callTransition ){
				LOG("[InitScene] Update -> callTransition\n");
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