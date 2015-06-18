 #include "stdafx.h"

#include "Layer.h"
#include "UserInterface.h"

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
			//this->LayerWrapper(smainscript->mainlayer_id, CreateLayer1(scene, pmainscript), scene);
		}

	}
}