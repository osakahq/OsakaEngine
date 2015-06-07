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
			virtual LayerDataPTR CreateMainLayer(RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript);
			virtual LayerDataPTR CreateFadeLayer(RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript);
			virtual PlaybackIntroScriptPTR CreateLayer1Script(PlaybackIntroCanvasPTR& canvas, RPGScenePTR& scene, PlaybackIntroSceneScriptPTR& mainscript);

			virtual PlaybackIntroCanvasPTR CreateLayer1Canvas();
		private:

		};
	}
}

#endif