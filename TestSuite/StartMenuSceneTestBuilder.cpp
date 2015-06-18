 #include "stdafx.h"

#include "Layer.h"
#include "UserInterface.h"

#include "TestStartMenuSceneScript.h"
#include "RPGScene.h"
#include "StartMenuSceneTestBuilder.h"

namespace Osaka{
	namespace TestSuite{
		StartMenuSceneTestBuilder::StartMenuSceneTestBuilder(){
			//There is an Init function in `SceneBuilder`. Don't forget to call it if overriden.
		}
		StartMenuSceneTestBuilder::~StartMenuSceneTestBuilder(){

		}
		RPGLib::SceneScript* StartMenuSceneTestBuilder::CreateMainScript(){
			//StartMenuSceneScriptPTR mainscript = std::make_shared<TestStartMenuSceneScript>(app);
			TestStartMenuSceneScript* mainscript = new TestStartMenuSceneScript(app);
			return mainscript;
		}
		
	}
}