 #include "stdafx.h"

#include "_testsuite_macro.h"
#include "TestPlaybackIntroScript.h"

namespace Osaka{
	namespace TestSuite{
		TestPlaybackIntroScript::TestPlaybackIntroScript(RPGLib::RPGApplicationPTR& app, RPGLib::RPGScenePTR& parent, RPGLib::PlaybackIntroCanvasPTR& canvas, RPGLib::PlaybackIntroSceneScriptPTR& mainscript)
			: PlaybackIntroScript(app, parent, canvas, mainscript){
			_is_loaded = false;
		}
		TestPlaybackIntroScript::~TestPlaybackIntroScript(){

		}
		
		void TestPlaybackIntroScript::Load(){
			PlaybackIntroScript::Load();
			_is_loaded = true;
		}
		
		void TestPlaybackIntroScript::End(){
			PlaybackIntroScript::End();

			OSAKA_ASSERT(_is_loaded);
		}
	}
}