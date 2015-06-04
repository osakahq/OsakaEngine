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
			RPGLib::PlaybackIntroScriptPTR CreateLayer1Script(RPGLib::PlaybackIntroCanvasPTR& canvas, RPGLib::RPGScenePTR& scene, RPGLib::PlaybackIntroSceneScriptPTR& mainscript) override;

		private:

		};
	}
}

#endif