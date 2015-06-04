 #include "stdafx.h"
#ifndef RPGLIB_RPGAPPLICATION_H
#define RPGLIB_RPGAPPLICATION_H

#include "EApplication.h"
#include "osaka_forward.h"
namespace Osaka{
	
	namespace RPGLib{
		
		class RPGApplication : public Engine::EApplication{
		public:
			RPGApplication(Debug::DebugPTR& d, Engine::SDLLibPTR& sdl, Engine::IFileLoaderPTR& fileloader, const bool _show_fpscounter);
			virtual ~RPGApplication();
			virtual void _delete();

			/* Owner. This has variables such as: volume, key controls, etc. */
			SettingsPTR settings;
			/* Owner. Holds all the data taken from the data game file */
			GameDataPTR gameData;

			/* Owner. RPGFactory is used for creating items, characters, npcs, etc. */
			FactoryPTR factory;
			RPGFactoryPTR rpgfactory;
			SceneFactoryPTR scenefactory;

			/* Owner */
			GameDataLoaderPTR loader;

			/* Owner. Class for the asset loading. Most of the functionality is done in the loadThread */
			AssetManagerPTR assetm;

			/* Owner. Ruler */
			RulerPTR ruler;
			/* Owner. This is the timer where the game relies on. */
			TimeManagerPTR timem;
			/* Owner */
			FPSCounterPTR counter;

			/* Check that the references are set */
			virtual void Init(bool vsync, int timePerFrame) override;

			/* Runs every frame */
			virtual void Update() override;
			virtual void BeforePresent() override;
			virtual void AfterPresent(const Uint32 frame_ms) override;
			/* Initializes the first scene and then passes it to EApplicacion (base class) */
			virtual void Run(const char* scene, Engine::ESceneArgsPTR& init_params);

			/* Only needs the id */
			void SetLoadingScene(std::string loadingscene_id);
			/* NOT Owner.  */
			void SetInitScene(InitScenePTR& scene);

			/* Owner of GameSession. */
			void SetGameSessionManager(GameSessionManagerPTR initialGSM);
			/* Doesn't give away ownership. */
			GameSessionManagerPTR GetGameSessionManager();

			//Function wrappers for RPGLoadingScene
			void FadeStackTransition(const char* scene, Engine::ESceneArgsPTR& params);
			void FadeSwitchTransition(const char* scene, Engine::ESceneArgsPTR& params);
			void LoadingStackTransition(const char* scene, Engine::ESceneArgsPTR& params);

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

			/* Scene: Responsible of adding the loading scene (itself) and calling GameLoader */
			std::string loadingscene_id;

			/* NOT Owner. 
			 * This is the very first scene that is added and the only thing that does is to make the call to add the real first scene */
			InitScenePTR initscene;

			/* Wether or not call FPSCounter (See Run/BeforePresent/AfterPresent) */
			const bool show_fpscounter;
		};
	}
}
#endif