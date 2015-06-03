 #include "stdafx.h"

#ifndef RPGLIB_LOADINGSCENEBUILDER_H
#define RPGLIB_LOADINGSCENEBUILDER_H

#include "SceneBuilder.h"

namespace Osaka{
	namespace RPGLib{

		class LoadingSceneBuilder : public SceneBuilder{
		public:
			LoadingSceneBuilder(AssetManagerPTR& assetmanager);
			virtual ~LoadingSceneBuilder();
		protected:
			
			virtual SceneScriptPTR CreateMainScript() override;
			virtual void CreateLayers(RPGScenePTR& scene, SceneScriptPTR& mainscript) override;
			virtual LayerDataPTR CreateFadeLayer(RPGScenePTR& scene, SceneScriptPTR& mainscript);
			
		private:
			/* NOT Owner */
			AssetManagerPTR assetmanager;
		};
	}
}

#endif