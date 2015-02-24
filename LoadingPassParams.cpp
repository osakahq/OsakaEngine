 #include "stdafx.h"
#include "EScenePassParams.h"
#include "LoadingPassParams.h"

namespace Osaka{
	namespace RPGLib{
		LoadingPassParams::LoadingPassParams() : Engine::EScenePassParams(){

		}
		LoadingPassParams::~LoadingPassParams(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingPassParams");
#endif	
			send_params = nullptr;
		}
	}
}