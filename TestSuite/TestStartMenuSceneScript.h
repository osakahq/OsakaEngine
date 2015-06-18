 #include "stdafx.h"
#ifndef TESTSUITE_TESTSTARTMENUSCENESCRIPT_H
#define TESTSUITE_TESTSTARTMENUSCENESCRIPT_H

#include <StartMenuSceneScript.h>

namespace Osaka{
	namespace TestSuite{
		
		class TestStartMenuSceneScript : public RPGLib::StartMenuSceneScript {
		public:
			TestStartMenuSceneScript(RPGLib::RPGApplication* app);
			~TestStartMenuSceneScript();
			
			void Load(RPGLib::RPGFactory& factory) override;
			void End() override;
		protected:
			
		private:
			bool is_loaded;
		};
	}
}

#endif;