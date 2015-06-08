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

#include "SceneFactory.h"
#include "InitScene.h"
#include "InitSceneArgs.h"

#include "FPSCounter.h"
#include "AssetManager.h"
#include "RPGScene.h"
#include "LoadingSceneScript.h"

#include "GameSessionManager.h"
#include "GameSession.h"
#include "Settings.h"
#include "GameData.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "Factory.h"
#include "RPGFactory.h"

#include "RPGApplicationBuilder.h"

namespace Osaka{
	namespace RPGLib{
		
		RPGApplicationBuilder::RPGApplicationBuilder(){

		}

		RPGApplicationPTR RPGApplicationBuilder::Create(const char* filedata, const char* filesettings, const char* pack_file, Debug::DebugPTR& debug){
			/* ----------------------------------------------------------------------- */
			/* --- Game Data --------------------------------------------------------- */
			GameDataPTR data = std::make_shared<GameData>();
			GameDataLoaderPTR loader = std::make_shared<GameDataLoader>(debug);
			loader->LoadGameFile(filedata, data);

			/* ----------------------------------------------------------------------- */
			/* --- App. At this point, the game data from the file is fully loaded. -- */
			Engine::IFileLoaderPTR fileloader;
#ifdef _DEBUG
			fileloader = std::make_shared<Engine::DefaultFileLoader>();
#else
			/* Only do this when everything is ready to go. */
			//fileloader = std::make_shared<Engine::PhysicsFSFileLoader>(debug, "tests\\tests.7z");
			fileloader = std::make_shared<Engine::DefaultFileLoader>();
#endif
			Engine::SDLLibPTR lib = std::make_shared<Engine::SDLLib>(debug);
			RPGApplicationPTR app = this->CreateRPGApp(debug, lib, fileloader);
			app->loader = loader;
			app->gameData = data;

			/* ----------------------------------------------------------------------- */
			/* --- Factory ----------------------------------------------------------- */
			FactoryPTR factory = std::make_shared<Factory>(debug);
			factory->sdl = lib;
			factory->fileloader = fileloader;
			factory->app = app;
			app->factory = factory;

			RPGFactoryPTR rpgfactory = std::make_shared<RPGFactory>(debug, data, factory);
			app->rpgfactory = rpgfactory;
			
			/* ------------------------------------------------------------------------ */
			/* --- Managers ----------------------------------------------------------- */
			TextureManagerPTR texturem = std::make_shared<TextureManager>(factory);
			texturem->SetSpritemaps(data->spritemaps, data->sprite_ids);
			
			FontManagerPTR fontm = std::make_shared<FontManager>(texturem, data->fontmap_error, data->fontmap_space_x, data->fontmap_space_y);
			fontm->SetFontmap(data->fontmap);
			
			SoundManagerPTR soundm = std::make_shared<SoundManager>(factory, lib);
			soundm->SetSounds(data->sounds);
			
			AssetManagerPTR assetm = std::make_shared<AssetManager>(debug, data->assets_type, data->assets_initload, data->assets_scenes);
			assetm->texturem = texturem;
			assetm->fontm = fontm;
			assetm->soundm = soundm;
			app->assetm = assetm;
			factory->assetm = assetm;

			TimeManagerPTR timem = std::make_shared<TimeManager>();
			app->timem = timem;
			factory->timem = timem;

			/* -------------------------------------------------------------------- */
			/* --- Misc ----------------------------------------------------------- */
			SettingsPTR settings = std::make_shared<Settings>(filesettings);
			app->settings = settings;

			RulerPTR ruler = std::make_shared<Ruler>(data->window_width, data->window_height);
			app->ruler = ruler;

			FPSCounterPTR counter = std::make_shared<FPSCounter>(data->target_fps, data->fontmap_space_x, data->fontmap_space_y, true);
			counter->Init(debug, fontm);
			app->counter = counter;

			/* -------------------------------------------------------------------- */
			/* --- Init ----------------------------------------------------------- */
			lib->Init(data->name.c_str(), data->window_width, data->window_height, data->default_render_color_data, data->vsync);
			lib->Start(); //Creates Hidden Window

			factory->Check();
			texturem->Init();
			soundm->Init();
			/* AssetManager must be after Texture/Sound because it loads the initial assets */
			assetm->Init(app);
			/* FontManager must be after AssetManager because it will call TextureManager to create sprite_data* and they have SDL_Texture* raw pointer */
			fontm->Init(*lib->GetRAWSDLRenderer());

			/* Builders. App/Factory MUST not have unset variables */
			app->scenefactory = this->CreateSceneFactory(factory, app, texturem);

			app->Init(data->vsync, data->time_per_frame, std::make_shared<GameSessionManager>(data));

			/* -------------------------------------------------------------------- */
			/* --- After this point, everything is loaded ------------------------------------------------------------------- */

			InitScenePTR initscene = factory->CreateInitScene();
			app->AddScene(initscene->GetId(), std::static_pointer_cast<Engine::EScene>(initscene));
			app->SetInitScene(initscene);

			/* RPGApplication stacks RPGScene (mainscript:LoadingSceneScript) then stacks the LoadingFade/LoadingTextLayer */
			RPGScenePTR loadingscene = app->scenefactory->CreateLoadingScene("rpglib_loadingscene");
			app->SetLoadingScene("rpglib_loadingscene");
			/* We need to call Load because the place to call `scene->Load()` is in AssetManager */
			loadingscene->Load();
			app->AddScene("rpglib_loadingscene", std::static_pointer_cast<Engine::EScene>(loadingscene));

			return app;
		}

		RPGApplicationPTR RPGApplicationBuilder::CreateRPGApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader){
			return std::make_shared<RPGLib::RPGApplication>(debug, sdl, fileloader, true);
		}

		SceneFactoryPTR RPGApplicationBuilder::CreateSceneFactory(FactoryPTR& factory, RPGApplicationPTR& app, TextureManagerPTR& texturem){
			return std::make_shared<SceneFactory>(factory, app, texturem);
		}

	}
}