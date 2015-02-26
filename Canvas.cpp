 #include "stdafx.h"
#include "SDLLib.h"
#include "RPGApplication.h"
#include "Canvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		Canvas::Canvas(RPGApplicationPTR& app){
			this->app = app;
			raw_renderer = app->sdl->GetRAWSDLRenderer();
		}
		Canvas::~Canvas(){
#ifdef _DEBUG
			_CHECKDELETE("Canvas");
#endif			
		}
		void Canvas::_delete(){
#ifdef _DEBUG
			_CHECKDELETE("Canvas_delete");
#endif
			raw_renderer = NULL;
			app = nullptr;
		}
	}
}