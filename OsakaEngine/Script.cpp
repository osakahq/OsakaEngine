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
		Script::Script(RPGApplication* app, RPGScene* scene_parent){
			this->app = app;
			this->scene_parent = scene_parent;
			layer_parent = NULL;
		}
		Script::~Script(){
#ifdef _DEBUG
			_CHECKDELETE("Script");
#endif		
			app = NULL;
			scene_parent = NULL;
			layer_parent = NULL;
		}
		
		void Script::Init(Layer* layer_parent){
			this->layer_parent = layer_parent;
		}

		/* These functions are not required to be implemented in the derived classes */
		void Script::Enter(){}
		void Script::Ready(LayerArgs& args){}
		void Script::Load(RPGFactory& factory){}
		void Script::Unload(){}
		void Script::Exit(){}

		void Script::Show(){}
		void Script::StandBy(){}
		void Script::Focus(){}
		void Script::End(){}

	}
}