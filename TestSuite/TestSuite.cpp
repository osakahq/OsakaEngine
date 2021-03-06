// TestSuite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Debug.h>
#include <ESceneArgs.h>
#include <LayerArgs.h>
#include "RPGLibTestSuite.h"
#include "_testsuite_macro.h"

using namespace Osaka;
using namespace Osaka::TestSuite;

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	TestSuite::RPGLibTestSuite* test = new TestSuite::RPGLibTestSuite();
	/* This is for faster OSAKA_ASSERT (macro) */
	OsakaAssertBegin(test);

	std::string resp;
	std::string phase = "";

	printf("[RPGLibTestSuite] Welcome\n");
	printf("[RPGLibTestSuite] Please select if you want to test [g]ameDataLoader or run [s]cene tests: ");
	std::getline(std::cin, resp);
			
	if( resp.length() == 2 ){
		//This way we can write s1 to fast forward the instructions.
		phase = resp.at(1);
		resp = resp.at(0);
	}

	if( resp == "g" ){
		test->IndividualTest_LoadGameFileTest("tests\\IndividualTest_LoadGameFileTest\\data.xml", false);
	}else if( resp == "s" ){
		/* We always do want to check delete */
#ifdef _DEBUG
		_STARTCHECKDELETE(false);
#endif

		if( phase == "" ){
			printf("\n[RPGLibTestSuite] Select a phase.\n");
			printf("\t- [1] for PHASE1. Tests -> Loading scene, AssetManager, PlaybackIntro scene and StartMenu scene\n");
			printf("\n[RPGLibTestSuite] Phase: ");
			std::getline(std::cin, phase);
		}

		TEST_PHASE::Value val = static_cast<TEST_PHASE::Value>(std::stoi(phase));
		test->Run(val);
	}else{
		printf("[RPGLibTestSuite] Invalid command. [g] or [s] only.\n");
	}

	test->CheckResults();
	/* Rember to always call `OsakaAssertEnd()` when `OsakaAssertBegin(...)` is called */
	OsakaAssertEnd();
	delete test; test = NULL;
			
#ifdef _DEBUG
	if( resp == "s" ){
		_ENDCHECKDELETE();
	}
#endif

	getchar();
	return 0;
}

