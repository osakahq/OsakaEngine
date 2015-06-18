 #include "stdafx.h"

#ifndef RPGLIB_LOADINGSCENEBUILDER_H
#define RPGLIB_LOADINGSCENEBUILDER_H

#include "SceneBuilder.h"

namespace Osaka{
	namespace RPGLib{

		class LoadingSceneBuilder : public SceneBuilder{
		public:
			LoadingSceneBuilder(AssetManager* assetmanager);
			virtual ~LoadingSceneBuilder();
		protected:
			
			virtual SceneScript* CreateMainScript() override;
			virtual void CreateLayers(RPGScene& scene, SceneScript& mainscript) override;
			virtual LayerData CreateFadeLayer(RPGScene& scene, LoadingSceneScript& mainscript);
			
		private:
			/* NOT Owner */
			AssetManager* assetmanager;
		};
	}
}

#endif