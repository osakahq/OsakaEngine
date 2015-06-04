 #include "stdafx.h"

#ifndef RPGLIB_PLAYBACKINTROSCENETESTBUILDER_H
#define RPGLIB_PLAYBACKINTROSCENETESTBUILDER_H

#include <PlaybackIntroSceneBuilder.h>

namespace Osaka{
	namespace RPGLib{

		class PlaybackIntroSceneTestBuilder : public PlaybackIntroSceneBuilder{
		public:
			PlaybackIntroSceneTestBuilder();
			~PlaybackIntroSceneTestBuilder();
		protected:
			PlaybackIntroScriptPTR CreateLayer1Script(PlaybackIntroCanvasPTR& canvas, RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript) override;

		private:

		};
	}
}

#endif