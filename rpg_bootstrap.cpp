 #include "stdafx.h"
#include "TimeManager.h"
#include "Ruler.h"
#include "Debug.h" 
#include "SDLLib.h"
#include "RPGApplication.h"
#include "IFileLoader.h"
#include "PhysicsFSFileLoader.h"
#include "DefaultFileLoader.h"
#include "GameDataLoader.h"

#include "FPSCounter.h"
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

#include "rpg_bootstrap.h"

namespace Osaka{
	namespace RPGLib{
		
		RPGApplicationPTR rpg_bootstrap(const char* filedata, const char* filesettings, Debug::DebugPTR& debug){
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
			RulerPTR ruler = std::make_shared<Ruler>(data->window_width, data->window_height);

			RPGApplicationPTR app = std::make_shared<RPGApplication>(debug, lib, fileloader);
			factory->renderer = lib->renderer;
			factory->fileloader = fileloader;
			factory->app = app;
			app->factory = factory;
			app->loader = loader;
			app->gameData = data;
			app->ruler = ruler;

			RPGFactoryPTR rpgfactory = std::make_shared<RPGFactory>(debug, data);
			app->rpgfactory = rpgfactory;
			
			SettingsPTR settings = std::make_shared<Settings>(filesettings);
			app->settings = settings;

			TextureManagerPTR texturem = std::make_shared<TextureManager>(factory);
			texturem->SetSpritemaps(data->spritemaps, data->sprite_ids);
			
			FontManagerPTR fontm = std::make_shared<FontManager>(texturem, data->fontmap_error, data->fontmap_space_x, data->fontmap_space_y);
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

			TimeManagerPTR timem = std::make_shared<TimeManager>();
			app->timem = timem;
			factory->timem = timem;

			FPSCounterPTR counter = std::make_shared<FPSCounter>(debug, fontm, data->target_fps);
			app->counter = counter;

			/* LoadingScene needs the name of the loadingscene so it can Stack/Switch the scene */
			RPGLoadingScenePTR loadingscene = factory->CreateRPGLoadingScene("rpglib_loadingscene");
			loadingscene->Load();
			app->SetLoadingScene(loadingscene);
			Engine::EScenePTR temp = loadingscene;
			app->AddScene("rpglib_loadingscene", temp);

			app->Init(data->vsync, data->time_per_frame);
			factory->Init();
			assetm->Init();

			return app;
		}
	}
}