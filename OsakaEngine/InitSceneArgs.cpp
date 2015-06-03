 #include "stdafx.h"
#include "ESceneArgs.h"
#include "InitSceneArgs.h"

namespace Osaka{
	namespace RPGLib{
		InitSceneArgs::InitSceneArgs() : Engine::ESceneArgs(){

		}
		InitSceneArgs::~InitSceneArgs(){
#ifdef _DEBUG
			_CHECKDELETE("InitSceneArgs");
#endif	
			init_args = nullptr;
		}
	}
}