 #include "stdafx.h"

#include "Factory.h"
#include "Layer.h"
#include "UserInterface.h"

#include "Image.h"
#include "Square.h"
#include "FadeInFadeOutEffect.h"
#include "FadeInOutScript.h"
#include "FadeInOutCanvas.h"

#include "RPGScene.h"
#include "TextureManager.h"
#include "PlaybackIntroSceneScript.h"
#include "PlaybackIntroScript.h"
#include "PlaybackIntroCanvas.h"
#include "PlaybackIntroSceneBuilder.h"

namespace Osaka{
	namespace RPGLib{
		PlaybackIntroSceneBuilder::PlaybackIntroSceneBuilder(){
			//There is an Init function in `SceneBuilder`. Don't forget to call it if overriden.
		}
		PlaybackIntroSceneBuilder::~PlaybackIntroSceneBuilder(){

		}
		SceneScript* PlaybackIntroSceneBuilder::CreateMainScript(){
			PlaybackIntroSceneScript* mainscript = new PlaybackIntroSceneScript(app);
			return mainscript;
		}
		void PlaybackIntroSceneBuilder::CreateLayers(RPGScene& scene, SceneScript& mainscript){
			PlaybackIntroSceneScript* pmainscript = dynamic_cast<PlaybackIntroSceneScript*>(&mainscript);
			
			/* The reason LayerWrapper has id_layer is that it can be safely overriden (`CreateMainLayer`, etc. functions) */
			this->LayerWrapper(pmainscript->mainlayer_id, CreateMainLayer(scene, *pmainscript), scene, mainscript);
			this->LayerWrapper(pmainscript->fadelayer_id, SceneBuilder::CreateFadeLayer(scene, *pmainscript), scene, mainscript);
		}

		LayerData PlaybackIntroSceneBuilder::CreateMainLayer(RPGScene& scene, PlaybackIntroSceneScript& mainscript){
			PlaybackIntroCanvas* canvas = CreateLayer1Canvas();
			PlaybackIntroScript* script = this->CreateLayer1Script(*canvas, scene, mainscript);
			UserInterface* ui = CreateDummyUI();

			//If i had custom inits:
			//LayerPTR layer = CreateAndInitLayer(...);
			//InitLayer1(); -> So that it can be overriden in child class.

			LayerData data(script, canvas, ui);
			return data;
		}
		
		PlaybackIntroScript* PlaybackIntroSceneBuilder::CreateLayer1Script(PlaybackIntroCanvas& canvas, RPGScene& scene, PlaybackIntroSceneScript& mainscript){
			return new PlaybackIntroScript(app, &scene, &canvas, &mainscript);
		}

		RPGLib::PlaybackIntroCanvas* PlaybackIntroSceneBuilder::CreateLayer1Canvas(){
			RPGLib::PlaybackIntroCanvas* canvas = new RPGLib::PlaybackIntroCanvas(this->raw_renderer, this->ruler);
			return canvas;
		}
	}
}