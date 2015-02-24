 // OsakaEngine.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Utils.h"
#include "EScenePassParams.h"
#include "RPGFactory.h"
#include "asc_bootstrap.h"
#include "Debug.h"
#include "ServerConn.h"
#include "RPGLibTestSuite.h"
#include "AscApplication.h"
#include "RPGApplication.h"
#include "osaka_forward.h"

#include "physfsrwops.h"
using namespace Osaka::RPGLib;
using namespace Osaka;

//moverla a rpg_bootstrap.cpp?
void bTestSuite(){
#ifdef _DEBUG
	_STARTCHECKDELETE();
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
	Engine::EmptyScenePassParamsPTR = nullptr;
#ifdef _DEBUG
	_ENDCHECKDELETE();
#endif
	getchar();
	std::exit(0);
}

void Ascension(){
//This main function is the owner of Debug and App
	Debug::DebugPTR debug = std::make_shared<Debug::Debug>("log.txt", true, Debug::DEBUG_LEVEL::CONSOLE);
	Network::ServerConnPTR conn = std::make_shared<Network::ServerConn>(debug);
	debug->init(conn);
	debug->l("[Ascension] ==========================================");
	
	//Asc::AscApplicationPTR app = Asc::asc_bootstrap("data\\ascension_data.xml", "data\\settings.xml", debug);
	Asc::AscApplicationPTR app = Asc::asc_bootstrap("tests\\runall_ascension_data.xml", "tests\\runall_settings.xml", debug);
	app->SetGameSessionManager(app->rpgfactory->CreateGameSessionManagerFromGameData());
	
	app->Run("startmenu");
	conn = nullptr;
	app->_delete(); app = nullptr;
	debug->_delete(); debug = nullptr;
}

int _tmain(int argc, _TCHAR* argv[])
{	
#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	//For tests:
	bTestSuite();
	//Ascension();
	/* Since we added a _CHECKDELETE in EScenePassParams, we need to free it before we exit the program */
	Engine::EmptyScenePassParamsPTR = nullptr;
	getchar();
	return 0;
}

