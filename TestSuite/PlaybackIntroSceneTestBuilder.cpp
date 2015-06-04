 #include "stdafx.h"

#include "PlaybackIntroScript.h"
#include "PlaybackIntroSceneTestBuilder.h"

namespace Osaka{
	namespace RPGLib{
		PlaybackIntroSceneTestBuilder::PlaybackIntroSceneTestBuilder(){
			//There is an Init function in `SceneBuilder`. Don't forget to call it if overriden.
		}
		PlaybackIntroSceneTestBuilder::~PlaybackIntroSceneTestBuilder(){

		}
		
		PlaybackIntroScriptPTR PlaybackIntroSceneTestBuilder::CreateLayer1Script(PlaybackIntroCanvasPTR& canvas, RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript){
			return std::make_shared<PlaybackIntroScript>(app, scene, canvas, mainscript);
		}

	}
}