 #include "stdafx.h"
#include "EScenePassParams.h"
#include "LoadingPassParams.h"

namespace Osaka{
	namespace RPGLib{
		LoadingPassParams::LoadingPassParams() : Engine::EScenePassParams(){

		}
		LoadingPassParams::~LoadingPassParams(){
			send_params = nullptr;
		}
	}
}