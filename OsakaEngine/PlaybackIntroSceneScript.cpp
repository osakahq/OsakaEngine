 #include "stdafx.h"
#include "Debug.h"
#include "ESceneArgs.h"
#include "LayerArgs.h"

#include "AssetManager.h"
#include "SoundManager.h"
#include "GameDataParams.h"
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
			app->soundm->PlayMusic(app->gameDataParams->intro_song);
		}
		void PlaybackIntroSceneScript::Ready(Engine::ESceneArgsPTR& params){
			scene_parent->Stack(mainlayer_id, EmptyLayerArgsPTR);
		}
	}
}