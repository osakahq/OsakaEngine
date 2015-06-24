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
#include "GameDataParams.h"
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

		RPGApplication* RPGApplicationBuilder::Create(const char* filedata, const char* filesettings, const char* pack_file, Debug::Debug& debug){
			/* ----------------------------------------------------------------------- */
			/* --- Game Data --------------------------------------------------------- */
			GameData* data = new GameData();
			GameDataLoader* loader = new GameDataLoader(&debug);
			loader->LoadGameFile(filedata, *data);

			/* ----------------------------------------------------------------------- */
			/* --- App. At this point, the game data from the file is fully loaded. -- */
			Engine::IFileLoader* fileloader;
#ifdef _DEBUG
			fileloader = new Engine::DefaultFileLoader();
#else
			/* Only do this when everything is ready to go. */
			//fileloader = std::make_shared<Engine::PhysicsFSFileLoader>(debug, "tests\\tests.7z");
			fileloader = new Engine::DefaultFileLoader();
#endif
			Engine::SDLLib* lib = new Engine::SDLLib(&debug);
			RPGApplication* app = this->CreateRPGApp(debug, *lib, *fileloader);
			app->loader = loader;
			app->gameData = data;

			GameDataParams* dataparams = this->CreateGameDataParams(*data);
			app->gameDataParams = dataparams;
			/* ----------------------------------------------------------------------- */
			/* --- Factory ----------------------------------------------------------- */
			Factory* factory = new Factory(&debug);
			factory->sdl = lib;
			factory->fileloader = fileloader;
			factory->app = app;
			app->factory = factory;

			RPGFactory* rpgfactory = new RPGFactory(&debug, data, dataparams, factory);
			app->rpgfactory = rpgfactory;
			
			/* ------------------------------------------------------------------------ */
			/* --- Managers ----------------------------------------------------------- */
			TextureManager* texturem = new TextureManager(factory);
			texturem->SetSpritemaps(data->spritemaps, data->sprite_ids);
			factory->texturem = texturem;
			app->texturem = texturem;

			FontManager* fontm = new FontManager(texturem, data->fontmap_error, data->fontmap_space_x, data->fontmap_space_y);
			fontm->SetFontmap(data->fontmap);
			app->fontm = fontm;

			SoundManager* soundm = new SoundManager(factory, lib);
			soundm->SetSounds(data->sounds);
			app->soundm = soundm;

			AssetManager* assetm = new AssetManager(&debug, data->assets_type, data->assets_initload, data->assets_scenes);
			assetm->texturem = texturem;
			assetm->fontm = fontm;
			assetm->soundm = soundm;
			app->assetm = assetm;
			factory->assetm = assetm;

			TimeManager* timem = new TimeManager();
			app->timem = timem;
			factory->timem = timem;

			/* -------------------------------------------------------------------- */
			/* --- Misc ----------------------------------------------------------- */
			Settings* settings = new Settings(filesettings);
			app->settings = settings;

			Ruler* ruler = new Ruler(data->window_width, data->window_height);
			app->ruler = ruler;

			FPSCounter* counter = new FPSCounter(data->target_fps, data->fontmap_space_x, data->fontmap_space_y, true);
			counter->Init(&debug, fontm);
			app->counter = counter;

			/* -------------------------------------------------------------------- */
			/* --- Init ----------------------------------------------------------- */
			lib->Init(data->name.c_str(), data->window_width, data->window_height, data->default_render_color_data, data->vsync);
			lib->Start(); //Creates Hidden Window

			factory->Check();
			rpgfactory->Init();
			texturem->Init();
			soundm->Init();
			/* AssetManager must be after Texture/Sound because it loads the initial assets */
			assetm->Init(app);
			/* FontManager must be after AssetManager because it will call TextureManager to create sprite_data* and they have SDL_Texture* raw pointer */
			fontm->Init(lib->GetRAWSDLRenderer());

			/* Builders. App/Factory MUST not have unset variables */
			app->scenefactory = this->CreateSceneFactory(*factory, *app, *texturem);

			app->Init(data->vsync, data->time_per_frame, data->max_updates_catch_up, new GameSessionManager(data));
			dataparams->SetParams();
			/* -------------------------------------------------------------------- */
			/* --- After this point, everything is loaded ------------------------------------------------------------------- */

			InitScene* initscene = factory->CreateInitScene();
			app->AddScene(initscene);
			app->SetInitScene(initscene);

			/* RPGApplication stacks RPGScene (mainscript:LoadingSceneScript) then stacks the LoadingFade/LoadingTextLayer */
			RPGScene* loadingscene = app->scenefactory->CreateLoadingScene("rpglib_loadingscene");
			app->SetLoadingScene("rpglib_loadingscene");
			/* We need to call Load because the place to call `scene->Load()` is in AssetManager */
			loadingscene->Load();
			app->AddScene(loadingscene);

			return app;
		}

		RPGApplication* RPGApplicationBuilder::CreateRPGApp(Debug::Debug& debug, Engine::SDLLib& sdl, Engine::IFileLoader& fileloader){
			return new RPGLib::RPGApplication(&debug, &sdl, &fileloader, true);
		}

		SceneFactory* RPGApplicationBuilder::CreateSceneFactory(Factory& factory, RPGApplication& app, TextureManager& texturem){
			return new SceneFactory(&factory, &app, &texturem);
		}

		GameDataParams* RPGApplicationBuilder::CreateGameDataParams(GameData& data){
			return new GameDataParams(&data);
		}
	}
}