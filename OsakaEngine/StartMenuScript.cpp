 #include "stdafx.h"

#include "StartMenuScript.h"

namespace Osaka{
	namespace RPGLib{

		StartMenuScript::StartMenuScript(RPGApplicationPTR& app, RPGScenePTR& parent, StartMenuCanvasPTR& canvas, StartMenuSceneScriptPTR& mainscript) : Script(app, parent){
			this->canvas = canvas;
			this->mainscript = mainscript;
		}
		StartMenuScript::~StartMenuScript(){

		}
		void StartMenuScript::_delete(){
			Script::_delete();
			canvas = nullptr;
			mainscript = nullptr;
		}
			
		void StartMenuScript::Update(){

		}

		void StartMenuScript::Ready(LayerArgsPTR& args){

		}

	}
}