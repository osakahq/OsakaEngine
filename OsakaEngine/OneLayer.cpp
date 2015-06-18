 #include "stdafx.h"

#include "OneLayerScript.h"
#include "Canvas.h"
#include "UserInterface.h"
#include "OneLayer.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		OneLayer::OneLayer(const std::string& id, OneLayerScript* script, Canvas* canvas, UserInterface* ui) : Layer(id, script, canvas, ui){
			this->onelayerscript = script;
		}
		OneLayer::~OneLayer(){
			onelayerscript = NULL;
		}
		
		void OneLayer::Ready(Engine::ESceneArgs& args){
			instack = true;
			//They are sent directly to the script.
			onelayerscript->Ready(args);
			raw_canvas->Ready();
			raw_ui->Ready();
		}
		
	}
}