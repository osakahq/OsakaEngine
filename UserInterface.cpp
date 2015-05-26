 #include "stdafx.h"
#include "SDLLib.h"
#include "RPGScene.h"
#include "RPGApplication.h"
#include "UserInterface.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		UserInterface::UserInterface(RPGApplicationPTR& app){
			this->app = app;
			raw_renderer = app->sdl->GetRAWSDLRenderer();
			parent = nullptr;
		}
		UserInterface::~UserInterface(){
#ifdef _DEBUG
			_CHECKDELETE("UserInterface");
#endif
		}
		void UserInterface::_delete(){
#ifdef _DEBUG
			_CHECKDELETE("UserInterface_delete");
#endif
			raw_renderer = NULL;
			app = nullptr;
			parent = nullptr;
		}

		void UserInterface::Init(RPGScenePTR& parent){
			this->parent = parent;
		}

		/* These functions are not required to be implemented in the derived classes */
		void UserInterface::Load(){}
		void UserInterface::Unload(){}
		void UserInterface::Ready(){}
		void UserInterface::Exit(){}

		void UserInterface::Show(){}
		void UserInterface::StandBy(){}
		void UserInterface::Focus(){}
	}
}