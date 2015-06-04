// Ascension.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <RPGScene.h>
#include <ESceneArgs.h>

#include <LayerArgs.h>

#include <Debug.h>
#include <ServerConn.h>
#include <SceneFactory.h>
#include <RPGFactory.h>
#include "AscApplicationBuilder.h"

#include "AscApplication.h"

#include "asc_forward.h"

using namespace Osaka;
using namespace Osaka::RPGLib;

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

#ifdef _DEBUG
	_STARTCHECKDELETE(true);
#endif
	//This main function is the owner of Debug and App
	Debug::DebugPTR debug = std::make_shared<Debug::Debug>("log.txt", true, Debug::DEBUG_LEVEL::CONSOLE);
	Network::ServerConnPTR conn = std::make_shared<Network::ServerConn>(debug);
	debug->init(conn);
	debug->l("[Ascension] Start");
	
	Asc::AscApplicationBuilder* appbuilder = new Asc::AscApplicationBuilder();
	Asc::AscApplicationPTR app = std::static_pointer_cast<Asc::AscApplication>(
		appbuilder->Create("tests\\runall_ascension_data.xml", "tests\\runall_settings.xml", "data\\data_01.opk", debug)
	);
	delete appbuilder;

	app->SetGameSessionManager(app->rpgfactory->CreateGameSessionManagerFromGameData());
	
	app->AddScene("test1", std::static_pointer_cast<Engine::EScene>(app->scenefactory->CreatePlaybackIntroScene("test1")));
	app->Run("test1", Engine::EmptyESceneArgsPTR);

	conn = nullptr;
	app->_delete(); app = nullptr;
	debug->_delete(); debug = nullptr;
	
#ifdef _DEBUG
	_ENDCHECKDELETE();
#endif

	getchar();
	return 0;
}

