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
		SceneScriptPTR StartMenuSceneBuilder::CreateMainScript(){
			StartMenuSceneScriptPTR mainscript = std::make_shared<StartMenuSceneScript>(app);
			return std::static_pointer_cast<SceneScript>(mainscript);
		}
		void StartMenuSceneBuilder::CreateLayers(RPGScenePTR& scene, SceneScriptPTR& mainscript){
			StartMenuSceneScriptPTR smainscript = std::dynamic_pointer_cast<StartMenuSceneScript>(mainscript);
			smainscript->SetLayers("enginelayer");
			//this->LayerWrapper(CreateLayer1(scene, pmainscript), scene);
		}

	}
}