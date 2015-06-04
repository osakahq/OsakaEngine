 #include "stdafx.h"

#include <PlaybackIntroScript.h>
#include "PlaybackIntroSceneTestBuilder.h"

namespace Osaka{
	namespace TestSuite{
		PlaybackIntroSceneTestBuilder::PlaybackIntroSceneTestBuilder(){
			//There is an Init function in `SceneBuilder`. Don't forget to call it if overriden.
		}
		PlaybackIntroSceneTestBuilder::~PlaybackIntroSceneTestBuilder(){

		}
		
		RPGLib::PlaybackIntroScriptPTR PlaybackIntroSceneTestBuilder::CreateLayer1Script(RPGLib::PlaybackIntroCanvasPTR& canvas, RPGLib::RPGScenePTR& scene, RPGLib::PlaybackIntroSceneScriptPTR& mainscript){
			return std::make_shared<RPGLib::PlaybackIntroScript>(app, scene, canvas, mainscript);
		}

	}
}