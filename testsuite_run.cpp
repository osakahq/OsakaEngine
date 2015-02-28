 #include "stdafx.h"

#include "Debug.h"
#include "ESceneArgs.h"
#include "RPGLibTestSuite.h"
#include "_testsuite_macro.h"
#include "testsuite_run.h"

namespace Osaka{
	namespace TestSuite{

		void run(){
			TestSuite::RPGLibTestSuitePTR test = std::make_shared<TestSuite::RPGLibTestSuite>();
			/* This is for faster OSAKA_ASSERT (macro) */
			OsakaAssertBegin(test);

			std::string resp;
			printf("[RPGLibTestSuite] Welcome\n");
			printf("[RPGLibTestSuite] Please select if you want to test [g]ameDataLoader or run [s]cene tests: ");
			std::getline(std::cin, resp);

			if( resp == "g" ){
				test->IndividualTest_LoadGameFileTest("tests\\IndividualTest_LoadGameFileTest\\data.xml", false);
			}else if( resp == "s" ){
				/* We always do want to check delete */
				_STARTCHECKDELETE(false);
				test->Run("test1");
			}else{
				printf("[RPGLibTestSuite] Invalid command. [g] or [s] only.\n");
			}

			test->CheckResults();
			/* Rember to always call `OsakaAssertEnd()` when `OsakaAssertBegin(...)` is called */
			OsakaAssertEnd();
			test->_delete(); 
			test = nullptr;

			if( resp == "s" ){
				_ENDCHECKDELETE();
			}
		}
	}
}