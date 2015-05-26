 #include "stdafx.h"
#include "SDLLib.h"
#include "RPGScene.h"
#include "RPGApplication.h"
#include "Script.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		Script::Script(RPGApplicationPTR& app){
			this->app = app;
			raw_renderer = app->sdl->GetRAWSDLRenderer();
			parent = nullptr;
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
			raw_renderer = NULL;
			app = nullptr;
			parent = nullptr;
		}

		void Script::Init(RPGScenePTR& parent){
			this->parent = parent;
		}

		/* These functions are not required to be implemented in the derived classes */
		void Script::Load(){}
		void Script::Unload(){}
		void Script::Exit(){}

		void Script::Show(){}
		void Script::StandBy(){}
		void Script::Focus(){}
		void Script::Draw(){}
	}
}