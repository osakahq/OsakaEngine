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
			mainlayer_id = "_mainlayer";
			fadelayer_id = "_fadelayer";
		}
		PlaybackIntroSceneScript::~PlaybackIntroSceneScript(){

		}
		void PlaybackIntroSceneScript::_delete(){
			SceneScript::_delete();
		}
		
		void PlaybackIntroSceneScript::Enter(){
			
		}
		void PlaybackIntroSceneScript::Ready(Engine::ESceneArgsPTR& params){
			scene_parent->Stack(mainlayer_id, EmptyLayerArgsPTR);
		}
	}
}