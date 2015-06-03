 #include "stdafx.h"

#include "Layer.h"
#include "UserInterface.h"

#include "RPGScene.h"
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
		SceneScriptPTR PlaybackIntroSceneBuilder::CreateMainScript(){
			PlaybackIntroSceneScriptPTR mainscript = std::make_shared<PlaybackIntroSceneScript>(app);
			mainscript->SetLayers("layer1");
			return std::static_pointer_cast<SceneScript>(mainscript);
		}
		void PlaybackIntroSceneBuilder::CreateLayers(RPGScenePTR& scene, SceneScriptPTR& mainscript){
			PlaybackIntroSceneScriptPTR pmainscript = std::dynamic_pointer_cast<PlaybackIntroSceneScript>(mainscript);
			this->LayerWrapper(CreateLayer1(scene, pmainscript), scene);
		}

		LayerDataPTR PlaybackIntroSceneBuilder::CreateLayer1(RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript){
			PlaybackIntroCanvasPTR canvas = std::make_shared<PlaybackIntroCanvas>(this->raw_renderer, this->ruler);
			PlaybackIntroScriptPTR script = this->CreateLayer1Script(canvas, scene, mainscript);
			UserInterfacePTR ui = CreateDummyUI();

			//If i had custom inits:
			//LayerPTR layer = CreateAndInitLayer(...);
			//InitLayer1(); -> So that it can be overriden in child class.

			LayerDataPTR data = std::make_shared<LayerData>("layer1", std::static_pointer_cast<Script>(script), std::static_pointer_cast<Canvas>(canvas), ui);
			return data;
		}
		PlaybackIntroScriptPTR PlaybackIntroSceneBuilder::CreateLayer1Script(PlaybackIntroCanvasPTR& canvas, RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript){
			return std::make_shared<PlaybackIntroScript>(app, scene, canvas, mainscript);
		}

	}
}