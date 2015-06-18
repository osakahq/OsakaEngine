 #include "stdafx.h"

#include "_testsuite_macro.h"
#include "TestPlaybackIntroScript.h"

namespace Osaka{
	namespace TestSuite{
		TestPlaybackIntroScript::TestPlaybackIntroScript(RPGLib::RPGApplication* app, RPGLib::RPGScene* parent, RPGLib::PlaybackIntroCanvas* canvas, RPGLib::PlaybackIntroSceneScript* mainscript)
			: PlaybackIntroScript(app, parent, canvas, mainscript){
			_is_loaded = false;
		}
		TestPlaybackIntroScript::~TestPlaybackIntroScript(){

		}
		
		void TestPlaybackIntroScript::Load(RPGLib::RPGFactory& factory){
			PlaybackIntroScript::Load(factory);
			_is_loaded = true;
		}
		
		void TestPlaybackIntroScript::End(){
			PlaybackIntroScript::End();

			OSAKA_ASSERTEX(TESTID_PHASE1_PLAYBACKLOAD, _is_loaded);
		}
	}
}