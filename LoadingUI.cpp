 #include "stdafx.h"
#include "UserInterface.h"
#include "LoadingUI.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		LoadingUI::LoadingUI(RPGApplicationPTR& app) : UserInterface(app){
		}
		LoadingUI::~LoadingUI(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingUI");
#endif
		}
		void LoadingUI::_delete(){
			UserInterface::_delete();
		}
		
		void LoadingUI::Update(){
		}
		void LoadingUI::Draw(){
		}
		
	}
}