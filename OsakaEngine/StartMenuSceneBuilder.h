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
			
			virtual SceneScriptPTR CreateMainScript() override;
			virtual void CreateLayers(RPGScenePTR& scene, SceneScriptPTR& mainscript) override;
			
		private:

		};
	}
}

#endif