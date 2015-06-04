 #include "stdafx.h"
#ifndef TESTSUITE_TESTPLAYBACKINTROSCRIPT_H
#define TESTSUITE_TESTPLAYBACKINTROSCRIPT_H

#include <PlaybackIntroScript.h>

namespace Osaka{
	namespace TestSuite{
		
		class TestPlaybackIntroScript: public RPGLib::PlaybackIntroScript{
		public:
			TestPlaybackIntroScript(RPGLib::RPGApplicationPTR& app, RPGLib::RPGScenePTR& parent, RPGLib::PlaybackIntroCanvasPTR& canvas, RPGLib::PlaybackIntroSceneScriptPTR& mainscript);
			~TestPlaybackIntroScript();
			
			void Load() override;
			void End() override;
		protected:
			
		private:
			bool _is_loaded;
		};
	}
}
#endif