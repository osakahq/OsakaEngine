 #include "stdafx.h"

#include "Layer.h"
#include "UserInterface.h"
#include "StartMenuCanvas.h"
#include "StartMenuScript.h"
#include "StartMenuSceneScript.h"
#include "RPGScene.h"
#include "StartMenuSceneBuilder.h"

namespace Osaka{
	namespace RPGLib{
		StartMenuSceneBuilder::StartMenuSceneBuilder(){
			//There is an Init function in `SceneBuilder`. Don't forget to call it if overriden.
		}
		StartMenuSceneBuilder::~StartMenuSceneBuilder(){

		}
		SceneScript* StartMenuSceneBuilder::CreateMainScript(){
			StartMenuSceneScript* mainscript = new StartMenuSceneScript(app);
			return mainscript;
		}
		void StartMenuSceneBuilder::CreateLayers(RPGScene& scene, SceneScript& mainscript){
			StartMenuSceneScript* smainscript = dynamic_cast<StartMenuSceneScript*>(&mainscript);
			this->LayerWrapper(smainscript->mainlayer_id, CreateMainLayer(scene, *smainscript), scene, mainscript);
		}

		LayerData StartMenuSceneBuilder::CreateMainLayer(RPGScene& scene, StartMenuSceneScript& mainscript){
			StartMenuCanvas* canvas = new StartMenuCanvas(this->raw_renderer, this->ruler);
			StartMenuScript* script = new StartMenuScript(app, &scene, canvas, &mainscript);
			UserInterface* ui = CreateDummyUI();

			LayerData data(script, canvas, ui);
			return data;
		}
	}
}