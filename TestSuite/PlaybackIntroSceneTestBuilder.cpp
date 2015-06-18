 #include "stdafx.h"

#include <TextureManager.h>
#include <Image.h>
#include <PlaybackIntroCanvas.h>
#include "TestPlaybackIntroScript.h"
#include "PlaybackIntroSceneTestBuilder.h"

namespace Osaka{
	namespace TestSuite{
		PlaybackIntroSceneTestBuilder::PlaybackIntroSceneTestBuilder(){
			//There is an Init function in `SceneBuilder`. Don't forget to call it if overriden.
		}
		PlaybackIntroSceneTestBuilder::~PlaybackIntroSceneTestBuilder(){
			
		}
		
		RPGLib::PlaybackIntroScript* PlaybackIntroSceneTestBuilder::CreateLayer1Script(RPGLib::PlaybackIntroCanvas& canvas, RPGLib::RPGScene& scene, RPGLib::PlaybackIntroSceneScript& mainscript){
			return new TestPlaybackIntroScript(app, &scene, &canvas, &mainscript);
		}

	}
}