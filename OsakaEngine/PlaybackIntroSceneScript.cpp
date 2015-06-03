 #include "stdafx.h"
#include "Debug.h"
#include "ESceneArgs.h"
#include "LayerArgs.h"

#include "RPGApplication.h"
#include "RPGScene.h"
#include "PlaybackIntroSceneScript.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		PlaybackIntroSceneScript::PlaybackIntroSceneScript(RPGApplicationPTR& app) 
			: SceneScript(app)
		{
			
		}
		PlaybackIntroSceneScript::~PlaybackIntroSceneScript(){

		}
		void PlaybackIntroSceneScript::_delete(){
			SceneScript::_delete();
		}
		void PlaybackIntroSceneScript::SetLayers(std::string layer1){
			//Remember there is an Init function. Only set the strings here.
			this->layer1 = layer1;
		}
		
		void PlaybackIntroSceneScript::Ready(Engine::ESceneArgsPTR& params){
			scene_parent->Stack(layer1, EmptyLayerArgsPTR);
		}
	}
}