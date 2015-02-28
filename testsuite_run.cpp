 #include "stdafx.h"

#include "ESceneArgs.h"
#include "RPGLibTestSuite.h"
#include "testsuite_run.h"

namespace Osaka{
	namespace TestSuite{
		void run(){
#ifdef _DEBUG
	_STARTCHECKDELETE(false);
#endif
	{
			TestSuite::RPGLibTestSuitePTR test = std::make_shared<TestSuite::RPGLibTestSuite>();
			//This runs all tests
			test->RunTests();
			//You can call individual tests
			//test->TestLoadGameFile(false);
			test->End();
			test->_delete(); test = nullptr;
	}
			Engine::EmptyESceneArgsPTR = nullptr;
#ifdef _DEBUG
	_ENDCHECKDELETE();
#endif
			getchar();
			std::exit(0);
		}
	}
}