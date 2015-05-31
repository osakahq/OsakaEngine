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

#include "InitScene.h"
#include "InitSceneArgs.h"

#include "FPSCounter.h"
#include "AssetManager.h"
#include "RPGScene.h"
#include "LoadingSceneScript.h"

#include "GameSession.h"
#include "Settings.h"
#include "GameData.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "Factory.h"
#include "RPGFactory.h"
#include "RPGApplicationCreator.h"

#include "rpg_bootstrap.h"

namespace Osaka{
	namespace RPGLib{
		
		RPGApplicationPTR rpg_bootstrap(const char* filedata, const char* filesettings, const char* pack_file, Debug::DebugPTR& debug, Utils::RPGApplicationCreatorPTR& appcreator){
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
			RPGApplicationPTR app = appcreator->CreateApp(debug, lib, fileloader);
			app->loader = loader;
			app->gameData = data;

			/* ----------------------------------------------------------------------- */
			/* --- Factory ----------------------------------------------------------- */
			FactoryPTR factory = std::make_shared<Factory>(debug);
			factory->sdl = lib;
			factory->fileloader = fileloader;
			factory->app = app;
			app->factory = factory;

			RPGFactoryPTR rpgfactory = std::make_shared<RPGFactory>(debug, data);
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

			FPSCounterPTR counter = std::make_shared<FPSCounter>(debug, fontm, data->target_fps, data->fontmap_space_x, data->fontmap_space_y);
			app->counter = counter;

			/* -------------------------------------------------------------------- */
			/* --- Init ----------------------------------------------------------- */
			lib->Init(data->name.c_str(), data->window_width, data->window_height, data->default_render_color_data, data->vsync);
			lib->Start(); //Creates Hidden Window

			factory->Check();
			texturem->Init();
			soundm->Init();
			/* AssetManager must be after Texture/Sound because it loads the initial assets */
			assetm->Init();
			/* FontManager must be after AssetManager because it will call TextureManager to create sprite_data* and they have SDL_Texture* raw pointer */
			fontm->Init(*lib->GetRAWSDLRenderer());

			app->Init(data->vsync, data->time_per_frame);

			/* -------------------------------------------------------------------- */
			/* --- After this point, everything is loaded ------------------------------------------------------------------- */

			InitScenePTR initscene = factory->CreateInitScene();
			app->AddScene(initscene->GetId(), std::static_pointer_cast<Engine::EScene>(initscene));
			app->SetInitScene(initscene);

			/* RPGApplication stacks RPGScene (mainscript:LoadingSceneScript) then stacks the LoadingFade/LoadingTextLayer */
			RPGScenePTR loadingscene = factory->CreateLoadingScene("rpglib_loadingscene");
			app->SetLoadingScene("rpglib_loadingscene");
			/* We need to call Load because the place to call `scene->Load()` is in AssetManager */
			loadingscene->Load();
			app->AddScene("rpglib_loadingscene", std::static_pointer_cast<Engine::EScene>(loadingscene));

			return app;
		}
	}
}