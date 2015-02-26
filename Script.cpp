 #include "stdafx.h"
#include "SDLLib.h"
#include "RPGApplication.h"
#include "Script.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		Script::Script(RPGApplicationPTR& app){
			this->app = app;
			raw_renderer = app->sdl->GetRAWSDLRenderer();
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
		}
	}
}