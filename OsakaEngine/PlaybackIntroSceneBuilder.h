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
			
			virtual SceneScriptPTR CreateMainScript() override;
			virtual void CreateLayers(RPGScenePTR& scene, SceneScriptPTR& mainscript) override;
			virtual LayerDataPTR CreateLayer1(RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript);
			virtual PlaybackIntroScriptPTR CreateLayer1Script(PlaybackIntroCanvasPTR& canvas, RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript);

		private:

		};
	}
}

#endif