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
		SceneScriptPTR PlaybackIntroSceneBuilder::CreateMainScript(){
			PlaybackIntroSceneScriptPTR mainscript = std::make_shared<PlaybackIntroSceneScript>(app);
			return std::static_pointer_cast<SceneScript>(mainscript);
		}
		void PlaybackIntroSceneBuilder::CreateLayers(RPGScenePTR& scene, SceneScriptPTR& mainscript){
			PlaybackIntroSceneScriptPTR pmainscript = std::dynamic_pointer_cast<PlaybackIntroSceneScript>(mainscript);
			
			/* The reason LayerWrapper has id_layer is that it can be safely overriden (`CreateMainLayer`, etc. functions) */
			this->LayerWrapper(pmainscript->mainlayer_id, CreateMainLayer(scene, pmainscript), scene, mainscript);
			this->LayerWrapper(pmainscript->fadelayer_id, CreateFadeLayer(scene, pmainscript), scene, mainscript);
		}

		LayerDataPTR PlaybackIntroSceneBuilder::CreateMainLayer(RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript){
			PlaybackIntroCanvasPTR canvas = CreateLayer1Canvas();
			PlaybackIntroScriptPTR script = this->CreateLayer1Script(canvas, scene, mainscript);
			UserInterfacePTR ui = CreateDummyUI();

			//If i had custom inits:
			//LayerPTR layer = CreateAndInitLayer(...);
			//InitLayer1(); -> So that it can be overriden in child class.

			LayerDataPTR data = std::make_shared<LayerData>(std::static_pointer_cast<Script>(script), std::static_pointer_cast<Canvas>(canvas), ui);
			return data;
		}
		LayerDataPTR PlaybackIntroSceneBuilder::CreateFadeLayer(RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript){
			SquarePTR square = std::make_shared<Square>(raw_renderer);
			FadeInFadeOutEffectPTR effect = std::make_shared<FadeInFadeOutEffect>(factory->CreateTimer());
			FadeInOutCanvasPTR canvas = std::make_shared<FadeInOutCanvas>(this->raw_renderer, this->ruler, square, effect);
			FadeInOutScriptPTR script = std::make_shared<FadeInOutScript>(app, scene, canvas);
			UserInterfacePTR ui = CreateDummyUI();

			LayerDataPTR data = std::make_shared<LayerData>(std::static_pointer_cast<Script>(script), std::static_pointer_cast<Canvas>(canvas), ui);
			return data;
		}
		PlaybackIntroScriptPTR PlaybackIntroSceneBuilder::CreateLayer1Script(PlaybackIntroCanvasPTR& canvas, RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript){
			return std::make_shared<PlaybackIntroScript>(app, scene, canvas, mainscript);
		}

		RPGLib::PlaybackIntroCanvasPTR PlaybackIntroSceneBuilder::CreateLayer1Canvas(){
			RPGLib::PlaybackIntroCanvasPTR canvas = std::make_shared<RPGLib::PlaybackIntroCanvas>(this->raw_renderer, this->ruler);
			return canvas;
		}
	}
}