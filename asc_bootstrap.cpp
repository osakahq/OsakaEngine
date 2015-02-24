 #include "stdafx.h"
#include "Debug.h" 
#include "SDLLib.h"
#include "RPGApplication.h"
#include "AscApplication.h"
#include "IFileLoader.h"
#include "PhysicsFSFileLoader.h"
#include "DefaultFileLoader.h"
#include "GameDataLoader.h"

#include "AssetManager.h"
#include "RPGLoadingScene.h"

#include "GameSession.h"
#include "Settings.h"
#include "GameData.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "Factory.h"
#include "RPGFactory.h"

#include "asc_bootstrap.h"
#include "asc_forward.h"

namespace Osaka{
	namespace Asc{
		using namespace RPGLib;

		AscApplicationPTR asc_bootstrap(const char* filedata, const char* filesettings, Debug::DebugPTR& debug){
			/*xxxxxxxxxxxxxxprintf("\n========\nTODO COPY WHATEVER THE CHANGES I DID TO RPG_BOOTSTRAP\n");
			FactoryPTR factory = std::make_shared<Factory>(debug);

			GameDataLoaderPTR loader = std::make_shared<GameDataLoader>(debug, factory);
			GameDataPTR data = loader->LoadGameFile(filedata);

			Engine::SDLLibPTR lib = std::make_shared<Engine::SDLLib>(debug);
			lib->Init(data->name.c_str(), data->window_width, data->window_height, data->default_render_color_data, data->vsync);
			lib->Start(); //Creates Hidden Window

			Engine::IFileLoaderPTR fileloader;
#ifdef _DEBUG
			fileloader = std::make_shared<Engine::DefaultFileLoader>();
#else
			//Only do this when everything is ready to go.
			fileloader = std::make_shared<Engine::PhysicsFSFileLoader>(debug, "tests\\tests.7z");
#endif
			AscApplicationPTR app = std::make_shared<AscApplication>(debug, lib, fileloader);
			factory->renderer = lib->renderer;
			factory->fileloader = fileloader;
			factory->app = app;
			app->factory = factory;
			app->loader = loader;
			app->gameData = data;

			RPGFactoryPTR rpgfactory = std::make_shared<RPGFactory>(debug, data);
			app->rpgfactory = rpgfactory;
			
			SettingsPTR settings = std::make_shared<Settings>(filesettings);
			app->settings = settings;

			TextureManagerPTR texturem = std::make_shared<TextureManager>(factory);
			texturem->SetSpritemaps(data->spritemaps, data->sprite_ids);
			
			FontManagerPTR fontm = std::make_shared<FontManager>(texturem, data->fontmap_error);
			fontm->SetFontmap(data->fontmap);
			
			SoundManagerPTR soundm = std::make_shared<SoundManager>(factory, lib);
			soundm->SetSounds(data->sounds);
			
			//-----------------------------------------------------------------------------
			AssetManagerPTR assetm = std::make_shared<AssetManager>(debug, data->assets_type, data->assets_initload, data->assets_scenes);
			assetm->texturem = texturem;
			assetm->fontm = fontm;
			assetm->soundm = soundm;
			app->assetm = assetm;
			factory->assetm = assetm;
			xxxxxxxxxxxxxxxxxxxxxx*/
			/* LoadingScene needs the name of the loadingscene so it can Stack/Switch the scene */
			/*RPGLoadingScenePTR loadingscene = factory->CreateRPGLoadingScene("rpglib_loadingscene");
			app->SetLoadingScene(loadingscene);
			Engine::EScenePTR temp = loadingscene;
			app->AddScene("rpglib_loadingscene", temp);

			app->Init(data->vsync, data->time_per_frame);
			factory->Init();
			assetm->Init();*/

			//return app;
			return nullptr;
		}
	}
}