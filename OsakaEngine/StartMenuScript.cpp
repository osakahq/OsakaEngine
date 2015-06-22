 #include "stdafx.h"

#include "StartMenuSceneScript.h"
#include "StartMenuCanvas.h"
#include "StartMenuScript.h"

namespace Osaka{
	namespace RPGLib{

		StartMenuScript::StartMenuScript(RPGApplication* app, RPGScene* parent, StartMenuCanvas* canvas, StartMenuSceneScript* mainscript) : Script(app, parent){
			this->canvas = canvas;
			this->mainscript = mainscript;
		}
		StartMenuScript::~StartMenuScript(){
			canvas = NULL;
			mainscript = NULL;
		}
			
		void StartMenuScript::Update(Engine::keyboard_state& state){

		}

		void StartMenuScript::Ready(LayerArgs& args){

		}

	}
}