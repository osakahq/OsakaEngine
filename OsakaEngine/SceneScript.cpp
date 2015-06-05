 #include "stdafx.h"

#include "RPGScene.h"
#include "RPGApplication.h"
#include "SceneScript.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		SceneScript::SceneScript(RPGApplicationPTR& app){
			this->app = app;
		}
		SceneScript::~SceneScript(){
#ifdef _DEBUG
			_CHECKDELETE("SceneScript");
#endif	
		}
		void SceneScript::_delete(){
			app = nullptr;
			scene_parent = nullptr;
		}
		void SceneScript::Init(RPGScenePTR& scene_parent){
			this->scene_parent = scene_parent;
		}
		/* These functions are not required to be implemented in the derived classes */
		void SceneScript::Ready(Engine::ESceneArgsPTR& args){}
		void SceneScript::Load(){}
		void SceneScript::Unload(){}
		void SceneScript::Exit(){}

		void SceneScript::Show(){}
		void SceneScript::StandBy(){}
		void SceneScript::Focus(){}

		void SceneScript::Update(){

		}
		void SceneScript::End(){}
	}
}