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
		StartMenuSceneScript::StartMenuSceneScript(RPGApplication* app) 
			: SceneScript(app), mainlayer_id("_mainlayer")
		{
			
		}
		StartMenuSceneScript::~StartMenuSceneScript(){
			
		}
		
		void StartMenuSceneScript::Ready(Engine::ESceneArgs& params){
			//TODO: scene_parent->Stack(layer1, EmptyLayerArgs);
		}
	}
}