 #include "stdafx.h"

#include "RPGScene.h"
#include "RPGApplication.h"
#include "SceneScript.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		SceneScript::SceneScript(RPGApplication* app){
			this->app = app;
		}
		SceneScript::~SceneScript(){
			app = NULL;
			scene_parent = NULL;
		}
		
		void SceneScript::Init(RPGScene* scene_parent){
			this->scene_parent = scene_parent;
		}
		/* These functions are not required to be implemented in the derived classes */
		void SceneScript::Enter(){}
		void SceneScript::Ready(Engine::ESceneArgs& args){}
		void SceneScript::Load(RPGFactory& factory){}
		void SceneScript::Unload(){}
		void SceneScript::Exit(){}

		void SceneScript::Show(){}
		void SceneScript::StandBy(){}
		void SceneScript::Focus(){}

		void SceneScript::Update(Engine::keyboard_state& state){

		}
		void SceneScript::End(){}
	}
}