 #include "stdafx.h"

#include "AssetManager.h"
#include "Factory.h"
#include "Layer.h"
#include "UserInterface.h"

#include "RPGScene.h"
#include "LoadingSceneScript.h"
#include "LoadingFadeScript.h"
#include "LoadingFadeCanvas.h"
#include "LoadingSceneBuilder.h"

namespace Osaka{
	namespace RPGLib{
		LoadingSceneBuilder::LoadingSceneBuilder(AssetManagerPTR& assetmanager){
			//There is an Init function in `SceneBuilder`. Don't forget to call it if overriden.
			this->assetmanager = assetmanager;
		}
		LoadingSceneBuilder::~LoadingSceneBuilder(){
			assetmanager = nullptr;
		}
		SceneScriptPTR LoadingSceneBuilder::CreateMainScript(){
			LoadingSceneScriptPTR mainscript = std::make_shared<LoadingSceneScript>(app, assetmanager);
			return std::static_pointer_cast<SceneScript>(mainscript);
		}
		void LoadingSceneBuilder::CreateLayers(RPGScenePTR& scene, SceneScriptPTR& mainscript){
			LoadingSceneScriptPTR lmainscript = std::dynamic_pointer_cast<LoadingSceneScript>(mainscript);
			this->LayerWrapper(lmainscript->fadelayer_id, CreateFadeLayer(scene, mainscript), scene, mainscript);
		}

		LayerDataPTR LoadingSceneBuilder::CreateFadeLayer(RPGScenePTR& scene, SceneScriptPTR& mainscript){
			LoadingFadeCanvasPTR canvas = std::make_shared<LoadingFadeCanvas>(this->raw_renderer, this->ruler, factory->CreateTimer());
			LoadingFadeScriptPTR script = std::make_shared<LoadingFadeScript>(app, scene, canvas, std::dynamic_pointer_cast<LoadingSceneScript>(mainscript));
			UserInterfacePTR ui = CreateDummyUI();

			//If i had custom inits:
			//LayerPTR layer = CreateAndInitLayer(...);
			//InitLayer1(); -> So that it can be overriden in child class.

			LayerDataPTR data = std::make_shared<LayerData>(std::static_pointer_cast<Script>(script), std::static_pointer_cast<Canvas>(canvas), ui);
			return data;
		}
		

	}
}