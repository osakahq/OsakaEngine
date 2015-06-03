 #include "stdafx.h"
#include "ESceneArgs.h"
namespace Osaka{
	namespace Engine{
		ESceneArgs::ESceneArgs(){

		}
		ESceneArgs::~ESceneArgs(){
#ifdef _DEBUG
			_CHECKDELETE("ESceneArgs");
#endif	
		}
		//Global empty params
		//EScenePassParams EmptyScenePassParams;
		std::shared_ptr<ESceneArgs> EmptyESceneArgsPTR = std::make_shared<ESceneArgs>();
	}
}