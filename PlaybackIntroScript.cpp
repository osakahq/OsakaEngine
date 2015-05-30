 #include "stdafx.h"

#include "RPGScene.h"
#include "PlaybackIntroSceneScript.h"
#include "RPGApplication.h"
#include "PlaybackIntroCanvas.h"
#include "PlaybackIntroScript.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		PlaybackIntroScript::PlaybackIntroScript(RPGApplicationPTR& app, RPGScenePTR& parent, PlaybackIntroCanvasPTR& canvas, PlaybackIntroSceneScriptPTR& mainscript)
			: Script(app, parent){
			
			this->canvas = canvas;
			this->mainscript = mainscript;
		}
		PlaybackIntroScript::~PlaybackIntroScript(){

		}
		void PlaybackIntroScript::_delete(){
			Script::_delete();

			canvas = nullptr;
			mainscript = nullptr;
		}

		void PlaybackIntroScript::Init(LayerPTR& layer_parent){
			Script::Init(layer_parent);
		}

		void PlaybackIntroScript::Ready(LayerArgsPTR& args){
			
		}

		void PlaybackIntroScript::Update(){
			
		}

	}
}