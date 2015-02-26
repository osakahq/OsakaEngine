 #include "stdafx.h"
#include "ESceneArgs.h"
#include "LoadingArgs.h"

namespace Osaka{
	namespace RPGLib{
		LoadingArgs::LoadingArgs() : Engine::ESceneArgs(){

		}
		LoadingArgs::~LoadingArgs(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingArgs");
#endif	
			send_params = nullptr;
		}
	}
}