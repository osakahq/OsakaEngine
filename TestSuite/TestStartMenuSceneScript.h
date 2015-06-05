 #include "stdafx.h"
#ifndef TESTSUITE_TESTSTARTMENUSCENESCRIPT_H
#define TESTSUITE_TESTSTARTMENUSCENESCRIPT_H

#include <StartMenuSceneScript.h>

namespace Osaka{
	namespace TestSuite{
		
		class TestStartMenuSceneScript : public RPGLib::StartMenuSceneScript {
		public:
			TestStartMenuSceneScript(RPGLib::RPGApplicationPTR& app);
			~TestStartMenuSceneScript();
			
			void Load() override;
			void End() override;
		protected:
			
		private:
			bool is_loaded;
		};
	}
}

#endif;