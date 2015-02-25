#include "stdafx.h"
#ifndef RPGLIB_RPGAPPLICATION_H
#define RPGLIB_RPGAPPLICATION_H

#include "EApplication.h"
#include "osaka_forward.h"
namespace Osaka{
	
	namespace RPGLib{
		
		class RPGApplication : public Engine::EApplication{
		public:
			RPGApplication(Debug::DebugPTR& d, Engine::SDLLibPTR& sdl, Engine::IFileLoaderPTR& fileloader);
			virtual ~RPGApplication();
			virtual void _delete();
			/* Owner. This has variables such as: volume, key controls, etc. */
			SettingsPTR settings;
			/* Owner. Holds all the data taken from the data game file */
			GameDataPTR gameData;

			/* Owner. RPGFactory is used for creating items, characters, npcs, etc. */
			FactoryPTR factory;
			RPGFactoryPTR rpgfactory;

			/* Owner */
			GameDataLoaderPTR loader;

			/* Owner. Class for the asset loading. Most of the functionality is done in the loadThread */
			AssetManagerPTR assetm;

			/* Owner. Ruler */
			RulerPTR ruler;
			/* Owner */
			TimeManagerPTR timem;
			/* Owner */
			FPSCounterPTR counter;

			/* Check that the references are set */
			virtual void Init(bool vsync, int timePerFrame);

			/* Runs every frame */
			virtual void Update();
			virtual void BeforePresent();
			virtual void RenderTime(Uint32 frame_ms);
			/* Initializes the first scene and then passes it to EApplicacion (base class) */
			virtual void Run(const char* scene);

			/* NOT Owner. The owner is in EApplication because the scene is inserted into the scene list */
			void SetLoadingScene(RPGLoadingScenePTR& scene);

			/* Owner of GameSession. */
			void SetGameSessionManager(GameSessionManagerPTR initialGSM);
			/* Doesn't give away ownership. */
			GameSessionManagerPTR GetGameSessionManager();

			//Function wrappers for RPGLoadingScene
			void SwitchTransition(const char* scene, Engine::EScenePassParamsPTR& params);
			void StackTransition(const char* scene, Engine::EScenePassParamsPTR& params);

			/* - gamesessionm_struct = rpgfactory->CreateGameSessionStructs(this.sessionm);
			 * - gameloader->savegame(gamesessionm_struct, filename); */
			void SaveGame(const char* filename);
			/* - delete current gamesessionmanager 
			 * - std::unordered_map<std::string, gamesession_data*>* gamesessions = gameloader->loadgame(const char* filename);
			 * - sessionm = rpgfactory->creategamesessionmanager(gamesessions);
			 * - */
			void LoadGame(const char* filename);

			/* It clears the gamesession manager/unload all the scenes that need to be resetted and switches to that scene */
			void ExitGame(const char* scene);

		/* ----------------------------------------------------------------------------------- */
		private:
			/* Owner. This has to be private because scenes need to be registered in order to get it. */
			GameSessionManagerPTR sessionm;

			/* NOT Owner. The owner is in EApplication because the scene is inserted into the scene list.
			 * Responsible of adding the loading scene (itself) and calling GameLoader */
			RPGLoadingScenePTR loadingscene;


			//This is used to insert the first scene. This needed because when you call `scene->Show()` it should be already inside the Run:loop
			/* 0 = initialized, 1 = first update(true), 2 = first update(false) */
			short firstUpdate;
			std::string first_scene;
		};
	}
}
#endif