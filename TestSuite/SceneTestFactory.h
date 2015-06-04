 #include "stdafx.h"

#ifndef RPGLIB_SCENETESTFACTORY_H
#define RPGLIB_SCENETESTFACTORY_H

#include <SceneFactory.h>

namespace Osaka{
	namespace RPGLib{

		class SceneTestFactory : public SceneFactory {
		public:
			SceneTestFactory(FactoryPTR& factory, RPGApplicationPTR& app);
			~SceneTestFactory();
			
			RPGScenePTR CreatePlaybackIntroScene(const char* name) override;
		
		};
	}
}

#endif