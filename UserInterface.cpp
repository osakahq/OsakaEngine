 #include "stdafx.h"
#include "SDLLib.h"
#include "RPGApplication.h"
#include "UserInterface.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		UserInterface::UserInterface(RPGApplicationPTR& app){
			this->app = app;
			raw_renderer = app->sdl->GetRAWSDLRenderer();
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
		}
	}
}