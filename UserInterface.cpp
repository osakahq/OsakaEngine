 #include "stdafx.h"
#include "RPGApplication.h"
#include "UserInterface.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		UserInterface::UserInterface(RPGApplicationPTR& app){
			this->app = app;
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
			app = nullptr;
		}
	}
}