 #include "stdafx.h"
#include "_testsuite_macro.h"
#include "Debug.h"
#include "ESceneArgs.h"
#include "LayerArgs.h"

#include "RPGApplication.h"
#include "RPGScene.h"
#include "TestStartMenuSceneScript.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace TestSuite{
		TestStartMenuSceneScript::TestStartMenuSceneScript(RPGLib::RPGApplicationPTR& app) 
			: StartMenuSceneScript(app)
		{
			is_loaded = false;
		}
		TestStartMenuSceneScript::~TestStartMenuSceneScript(){

		}
		
		void TestStartMenuSceneScript::Load(RPGLib::RPGFactoryPTR& factory){
			StartMenuSceneScript::Load(factory);
			is_loaded = true;
		}

		void TestStartMenuSceneScript::End(){
			StartMenuSceneScript::End();

			OSAKA_ASSERTEX(TESTID_PHASE1_PLAYBACKLOAD_LINKED, is_loaded);
		}
	}
}