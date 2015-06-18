 #include "stdafx.h"
#ifndef RPGLIB_RPGAPPLICATIONBUILDER_H
#define RPGLIB_RPGAPPLICATIONBUILDER_H
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class RPGApplicationBuilder{
		public:
			RPGApplicationBuilder();
			RPGApplication* Create(const char* filedata, const char* filesettings, const char* pack_file, Debug::Debug& debug);

		protected:
			//I can also add variables so that I don't have to pass around parameters.
			//You have to store the references in here if for example, RPGApp needs something else in constructor
			virtual RPGApplication* CreateRPGApp(Debug::Debug& debug, Engine::SDLLib& sdl, Engine::IFileLoader& fileloader);
			virtual SceneFactory* CreateSceneFactory(Factory& factory, RPGApplication& app, TextureManager& texturem);
			virtual GameDataParams* CreateGameDataParams(GameData& data);
		};
		
	}
}
#endif