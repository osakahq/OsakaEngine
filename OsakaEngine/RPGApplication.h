 #include "stdafx.h"
#ifndef RPGLIB_RPGAPPLICATION_H
#define RPGLIB_RPGAPPLICATION_H

#include "EApplication.h"
#include "osaka_forward.h"
namespace Osaka{
	
	namespace RPGLib{
		
		class RPGApplication : public Engine::EApplication{
		public:
			RPGApplication(Debug::Debug* d, Engine::SDLLib* sdl, Engine::IFileLoader* fileloader, const bool _show_fpscounter);
			virtual ~RPGApplication();
			
			/* Owner. This has variables such as: volume, key controls, etc. */
			Settings* settings;
			/* Owner. Holds all the data taken from the data game file */
			GameData* gameData;
			/* Owner. Holds the params. ID's, etc. This is used in Scene:Load(rpgfactory) */
			GameDataParams* gameDataParams;

			/* Owner. RPGFactory is used for creating items, characters, npcs, etc. */
			Factory* factory;
			RPGFactory* rpgfactory;
			SceneFactory* scenefactory;

			/* Owner */
			GameDataLoader* loader;

			/* Owner. Class for the asset loading. Most of the functionality is done in the loadThread */
			AssetManager* assetm;
			/* Owner */
			TextureManager* texturem;
			/* Owner */
			FontManager* fontm;
			/* Owner */
			SoundManager* soundm;

			/* Owner. Ruler */
			Ruler* ruler;
			/* Owner. This is the timer where the game relies on. */
			TimeManager* timem;
			/* Owner */
			FPSCounter* counter;

			/* Check that the references are set */
			virtual void Init(bool vsync, int timePerFrame, int maxUpdatesToCatchUp, GameSessionManager* gsm);

			/* Overrides so that it can send RPGFactory */
			virtual void CallLoad(const std::string& id) override;
			
			virtual void Update(const Uint32 delta) override;

			virtual void BeforePresent() override;
			virtual void AfterPresent(const Uint32 started) override;
			/* Initializes the first scene and then passes it to EApplicacion (base class) */
			virtual void Run(const std::string& scene, Engine::ESceneArgsPTR& init_params);
			virtual void End();

			/* Only needs the id */
			void SetLoadingScene(const std::string& loadingscene_id);
			/* NOT Owner.  */
			void SetInitScene(InitScene* scene);

			/* Doesn't give away ownership. */
			GameSessionManager* GetGameSessionManager();

			//Function wrappers for RPGLoadingScene
			void FadeStackTransition(const std::string& scene, const Engine::ESceneArgsPTR& params);
			void FadeSwitchTransition(const std::string& scene, const Engine::ESceneArgsPTR& params);
			void LoadingStackTransition(const std::string& scene, const Engine::ESceneArgsPTR& params);

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
			GameSessionManager* gsm;

			/* Scene: Responsible of adding the loading scene (itself) and calling GameLoader */
			std::string loadingscene_id;

			/* NOT Owner. 
			 * This is the very first scene that is added and the only thing that does is to make the call to add the real first scene */
			InitScene* initscene;

			/* Wether or not call FPSCounter (See Run/BeforePresent/AfterPresent) */
			const bool show_fpscounter;

			/* A temp variable. Owner. */
			LoadingArgs* args;
		};
	}
}
#endif