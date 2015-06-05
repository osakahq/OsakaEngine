 #include "stdafx.h"
#include "Debug.h"
#include "ESceneArgs.h"
#include "LayerArgs.h"

#include "RPGApplication.h"
#include "RPGScene.h"
#include "StartMenuSceneScript.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		StartMenuSceneScript::StartMenuSceneScript(RPGApplicationPTR& app) 
			: SceneScript(app)
		{
			
		}
		StartMenuSceneScript::~StartMenuSceneScript(){

		}
		void StartMenuSceneScript::_delete(){
			SceneScript::_delete();
		}
		void StartMenuSceneScript::SetLayers(std::string enginelogo_layer){
			//Remember there is an Init function. Only set the strings here.
			this->enginelogo_layer = enginelogo_layer;
		}
		
		void StartMenuSceneScript::Ready(Engine::ESceneArgsPTR& params){
			//TODO: scene_parent->Stack(layer1, EmptyLayerArgsPTR);
		}
	}
}