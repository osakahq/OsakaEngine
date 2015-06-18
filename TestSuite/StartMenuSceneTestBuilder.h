 #include "stdafx.h"

#ifndef TESTSUITE_STARTMENUSCENETESTBUILDER_H
#define TESTSUITE_STARTMENUSCENETESTBUILDER_H

#include <StartMenuSceneBuilder.h>

namespace Osaka{
	namespace TestSuite{

		class StartMenuSceneTestBuilder : public RPGLib::StartMenuSceneBuilder{
		public:
			StartMenuSceneTestBuilder();
			~StartMenuSceneTestBuilder();
		protected:
			
			virtual RPGLib::SceneScript* CreateMainScript() override;
			
		private:

		};
	}
}

#endif