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
		LoadingSceneBuilder::LoadingSceneBuilder(AssetManager* assetmanager){
			//There is an Init function in `SceneBuilder`. Don't forget to call it if overriden.
			this->assetmanager = assetmanager;
		}
		LoadingSceneBuilder::~LoadingSceneBuilder(){
			assetmanager = NULL;
		}
		SceneScript* LoadingSceneBuilder::CreateMainScript(){
			LoadingSceneScript* mainscript = new LoadingSceneScript(app, assetmanager);
			return mainscript;
		}
		void LoadingSceneBuilder::CreateLayers(RPGScene& scene, SceneScript& mainscript){
			LoadingSceneScript* lmainscript = dynamic_cast<LoadingSceneScript*>(&mainscript);
			this->LayerWrapper(lmainscript->fadelayer_id, CreateFadeLayer(scene, *lmainscript), scene, mainscript);
		}

		LayerData LoadingSceneBuilder::CreateFadeLayer(RPGScene& scene, LoadingSceneScript& mainscript){
			LoadingFadeCanvas* canvas = new LoadingFadeCanvas(this->raw_renderer, this->ruler, factory->CreateTimer());
			LoadingFadeScript* script = new LoadingFadeScript(app, &scene, canvas, &mainscript);
			UserInterface* ui = CreateDummyUI();

			//If i had custom inits:
			//LayerPTR layer = CreateAndInitLayer(...);
			//InitLayer1(); -> So that it can be overriden in child class.

			LayerData data(script, canvas, ui);
			return data;
		}
		

	}
}