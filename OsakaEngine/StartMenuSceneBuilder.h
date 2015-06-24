 #include "stdafx.h"

#ifndef RPGLIB_STARTMENUSCENEBUILDER_H
#define RPGLIB_STARTMENUSCENEBUILDER_H

#include "SceneBuilder.h"

namespace Osaka{
	namespace RPGLib{

		class StartMenuSceneBuilder : public SceneBuilder{
		public:
			StartMenuSceneBuilder();
			virtual ~StartMenuSceneBuilder();
		protected:
			
			virtual SceneScript* CreateMainScript() override;
			virtual void CreateLayers(RPGScene& scene, SceneScript& mainscript) override;
			LayerData StartMenuSceneBuilder::CreateMainLayer(RPGScene& scene, StartMenuSceneScript& mainscript);
		private:

		};
	}
}

#endif