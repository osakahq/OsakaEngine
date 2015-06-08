 #include "stdafx.h"
#include "SDLLib.h"
#include "Layer.h"
#include "LayerArgs.h"
#include "RPGScene.h"
#include "RPGApplication.h"
#include "Script.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		Script::Script(RPGApplicationPTR& app, RPGScenePTR& scene_parent){
			this->app = app;
			this->scene_parent = scene_parent;
		}
		Script::~Script(){
#ifdef _DEBUG
			_CHECKDELETE("Script");
#endif		
		}
		void Script::_delete(){
#ifdef _DEBUG
			_CHECKDELETE("Script_delete");
#endif
			app = nullptr;
			scene_parent = nullptr;
			layer_parent = nullptr;
		}

		void Script::Init(LayerPTR& layer_parent){
			this->layer_parent = layer_parent;
		}

		/* These functions are not required to be implemented in the derived classes */
		void Script::Enter(){}
		void Script::Ready(LayerArgsPTR& args){}
		void Script::Load(RPGFactoryPTR& factory){}
		void Script::Unload(){}
		void Script::Exit(){}

		void Script::Show(){}
		void Script::StandBy(){}
		void Script::Focus(){}
		void Script::End(){}

	}
}