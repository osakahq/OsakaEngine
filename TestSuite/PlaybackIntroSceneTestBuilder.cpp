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
		
		RPGLib::PlaybackIntroScriptPTR PlaybackIntroSceneTestBuilder::CreateLayer1Script(RPGLib::PlaybackIntroCanvasPTR& canvas, RPGLib::RPGScenePTR& scene, RPGLib::PlaybackIntroSceneScriptPTR& mainscript){
			return std::make_shared<TestPlaybackIntroScript>(app, scene, canvas, mainscript);
		}

		RPGLib::PlaybackIntroCanvasPTR PlaybackIntroSceneTestBuilder::CreateLayer1Canvas(){
			RPGLib::PlaybackIntroCanvasPTR canvas = std::make_shared<RPGLib::PlaybackIntroCanvas>(this->raw_renderer, this->ruler, TEST_TEXTURE_ENGINELOGO, TEST_TEXTURE_GAMESTUDIOLOGO);
			return canvas;
		}
	}
}