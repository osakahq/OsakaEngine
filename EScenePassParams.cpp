 #include "stdafx.h"
#include "EScenePassParams.h"
namespace Osaka{
	namespace Engine{
		EScenePassParams::EScenePassParams(){

		}
		EScenePassParams::~EScenePassParams(){
#ifdef _DEBUG
			_CHECKDELETE("EScenePassParams");
#endif	
		}
		//Global empty params
		//EScenePassParams EmptyScenePassParams;
		std::shared_ptr<EScenePassParams> EmptyScenePassParamsPTR = std::make_shared<EScenePassParams>();
	}
}