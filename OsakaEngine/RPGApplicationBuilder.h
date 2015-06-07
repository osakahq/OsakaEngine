 #include "stdafx.h"
#ifndef RPGLIB_RPGAPPLICATIONBUILDER_H
#define RPGLIB_RPGAPPLICATIONBUILDER_H
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class RPGApplicationBuilder{
		public:
			RPGApplicationBuilder();
			RPGApplicationPTR Create(const char* filedata, const char* filesettings, const char* pack_file, Debug::DebugPTR& debug);

		protected:
			//I can also add variables so that I don't have to pass around parameters.
			//You have to store the references in here if for example, RPGApp needs something else in constructor
			virtual RPGApplicationPTR CreateRPGApp(Debug::DebugPTR debug, Engine::SDLLibPTR sdl, Engine::IFileLoaderPTR fileloader);
			virtual SceneFactoryPTR CreateSceneFactory(FactoryPTR& factory, RPGApplicationPTR& app, TextureManagerPTR& texturem);
		};
		
	}
}
#endif