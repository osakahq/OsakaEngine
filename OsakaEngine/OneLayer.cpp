 #include "stdafx.h"

#include "OneLayerScript.h"
#include "Canvas.h"
#include "UserInterface.h"
#include "OneLayer.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		OneLayer::OneLayer(std::string id, OneLayerScriptPTR& script, CanvasPTR& canvas, UserInterfacePTR& ui) : Layer(id, std::static_pointer_cast<Script>(script), canvas, ui){
			this->onelayerscript = script;
		}
		OneLayer::~OneLayer(){
			
		}
		
		void OneLayer::_delete(){
			Layer::_delete();
			this->onelayerscript = nullptr;
		}

		void OneLayer::Ready(Engine::ESceneArgsPTR& args){
			instack = true;
			//They are sent directly to the script.
			onelayerscript->Ready(args);
			canvas->Ready();
			ui->Ready();
		}
		
	}
}