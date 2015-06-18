 #include "stdafx.h"
#ifndef TESTSUITE_TESTPLAYBACKINTROSCRIPT_H
#define TESTSUITE_TESTPLAYBACKINTROSCRIPT_H

#include <PlaybackIntroScript.h>

namespace Osaka{
	namespace TestSuite{
		
		class TestPlaybackIntroScript: public RPGLib::PlaybackIntroScript{
		public:
			TestPlaybackIntroScript(RPGLib::RPGApplication* app, RPGLib::RPGScene* parent, RPGLib::PlaybackIntroCanvas* canvas, RPGLib::PlaybackIntroSceneScript* mainscript);
			~TestPlaybackIntroScript();
			
			void Load(RPGLib::RPGFactory& factory) override;
			void End() override;
		protected:
			
		private:
			bool _is_loaded;
		};
	}
}
#endif