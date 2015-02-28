 // OsakaEngine.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "EScene.h"
#include "RPGScene.h"
#include "ESceneArgs.h"

#include "Debug.h"
#include "ServerConn.h"

#include "Factory.h"
#include "RPGFactory.h"
#include "rpg_bootstrap.h"

#include "AscApplicationCreator.h"
#include "AscApplication.h"

#include "testsuite_run.h"

#include "osaka_forward.h"
#include "asc_forward.h"

using namespace Osaka::RPGLib;
using namespace Osaka;

void Ascension(){
#ifdef _DEBUG
	_STARTCHECKDELETE(true);
#endif
	//This main function is the owner of Debug and App
	Debug::DebugPTR debug = std::make_shared<Debug::Debug>("log.txt", true, Debug::DEBUG_LEVEL::CONSOLE);
	Network::ServerConnPTR conn = std::make_shared<Network::ServerConn>(debug);
	debug->init(conn);
	debug->l("[Ascension] Start");
	
	Asc::AscApplicationCreatorPTR appcreator = std::make_shared<Asc::AscApplicationCreator>();
	Asc::AscApplicationPTR app = std::static_pointer_cast<Asc::AscApplication>(
		RPGLib::rpg_bootstrap("tests\\runall_ascension_data.xml", "tests\\runall_settings.xml", "data\\data_01.opk", debug, std::static_pointer_cast<Utils::ApplicationCreator>(appcreator))
	);
	appcreator = nullptr;

	app->SetGameSessionManager(app->rpgfactory->CreateGameSessionManagerFromGameData());
	
	app->AddScene("test1", std::static_pointer_cast<Engine::EScene>(app->factory->CreatePlaybackIntroScene("test1")));
	app->Run("test1");

	conn = nullptr;
	app->_delete(); app = nullptr;
	debug->_delete(); debug = nullptr;
	
#ifdef _DEBUG
	_ENDCHECKDELETE();
#endif
}

int _tmain(int argc, _TCHAR* argv[])
{	
#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	TestSuite::run();
	//Ascension();

	/* Since we added a _CHECKDELETE in EScenePassParams, we need to free it before we exit the program 
	 * or EmptyScenePassParamsPTR will call to a disposed function (when the program exits) */
	Engine::EmptyESceneArgsPTR = nullptr;

	getchar();
	return 0;
}

