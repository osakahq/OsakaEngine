 #include "stdafx.h"

#ifndef RPGLIB_PLAYBACKINTROSCENEBUILDER_H
#define RPGLIB_PLAYBACKINTROSCENEBUILDER_H

#include "SceneBuilder.h"

namespace Osaka{
	namespace RPGLib{

		class PlaybackIntroSceneBuilder : public SceneBuilder{
		public:
			PlaybackIntroSceneBuilder();
			virtual ~PlaybackIntroSceneBuilder();
		protected:
			
			virtual SceneScript* CreateMainScript() override;
			virtual void CreateLayers(RPGScene& scene, SceneScript& mainscript) override;
			virtual LayerData CreateMainLayer(RPGScene& scene, PlaybackIntroSceneScript& mainscript);
			virtual LayerData CreateFadeLayer(RPGScene& scene, PlaybackIntroSceneScript& mainscript);
			virtual PlaybackIntroScript* CreateLayer1Script(PlaybackIntroCanvas& canvas, RPGScene& scene, PlaybackIntroSceneScript& mainscript);

			virtual PlaybackIntroCanvas* CreateLayer1Canvas();
		private:

		};
	}
}

#endif