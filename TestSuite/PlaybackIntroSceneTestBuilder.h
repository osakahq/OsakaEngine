 #include "stdafx.h"

#ifndef RPGLIB_PLAYBACKINTROSCENETESTBUILDER_H
#define RPGLIB_PLAYBACKINTROSCENETESTBUILDER_H

#include <PlaybackIntroSceneBuilder.h>

namespace Osaka{
	namespace TestSuite{

		class PlaybackIntroSceneTestBuilder : public RPGLib::PlaybackIntroSceneBuilder{
		public:
			PlaybackIntroSceneTestBuilder();
			~PlaybackIntroSceneTestBuilder();

		protected:
			RPGLib::PlaybackIntroScript* CreateLayer1Script(RPGLib::PlaybackIntroCanvas& canvas, RPGLib::RPGScene& scene, RPGLib::PlaybackIntroSceneScript& mainscript) override;

			RPGLib::FadeInOutCanvas* CreateFadeInOutCanvas() override;
		private:
			
		};
	}
}

#endif