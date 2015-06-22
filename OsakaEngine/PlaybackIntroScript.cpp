 #include "stdafx.h"

#include "Debug.h"
#include "RPGScene.h"
#include "PlaybackIntroSceneScript.h"
#include "RPGApplication.h"
#include "PlaybackIntroCanvas.h"
#include "PlaybackIntroScript.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		PlaybackIntroScript::PlaybackIntroScript(RPGApplication* app, RPGScene* parent, PlaybackIntroCanvas* canvas, PlaybackIntroSceneScript* mainscript)
			: Script(app, parent){
			
			this->canvas = canvas;
			this->mainscript = mainscript;
		}
		PlaybackIntroScript::~PlaybackIntroScript(){
			canvas = NULL;
			mainscript = NULL;
		}
		
		void PlaybackIntroScript::Init(Layer* layer_parent){
			Script::Init(layer_parent);
		}
		void PlaybackIntroScript::Load(RPGFactory& factory){
			//called from the loading thread.
			LOG("[PlaybackIntroScript] Load called.\n");
		}
		void PlaybackIntroScript::Ready(LayerArgs& args){
			
		}

		void PlaybackIntroScript::Update(Engine::keyboard_state& state){
			
		}

	}
}