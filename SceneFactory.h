 #include "stdafx.h"

#ifndef RPGLIB_SCENEFACTORY_H
#define RPGLIB_SCENEFACTORY_H

#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class SceneFactory {
		public:
			SceneFactory(FactoryPTR& factory, RPGApplicationPTR& app);
			~SceneFactory();
			void _delete();

			RPGScenePTR CreateLoadingScene(const char* name);
			RPGScenePTR CreatePlaybackIntroScene(const char* name);
			/* This should be not in here... (TestSuite) */
			RPGScenePTR CreatePlaybackIntroScene_Test(const char* name);
		protected:
			
		private:
			/* NOT Owner */
			FactoryPTR factory;
			/* NOT Owner */
			RPGApplicationPTR app;
		};
	}
}

#endif