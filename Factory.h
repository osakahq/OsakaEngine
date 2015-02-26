 #include "stdafx.h"
#ifndef RPGLIB_FACTORY_H
#define RPGLIB_FACTORY_H
#include "osaka_forward.h"
struct SDL_Renderer;

namespace Osaka{
	
	namespace RPGLib{
		
		class Factory{
		public:
			Factory(Debug::DebugPTR& debug);
			~Factory();
			void _delete();
			/* Check that the references are set */
			void Init();

			// Gives away ownership.
			GameDataPTR CreateGameData();
			Engine::TexturePTR CreateTexture();
			Engine::SoundPTR CreateSound(sound_dataPTR& data);
			// Scenes
			RPGLoadingScenePTR CreateRPGLoadingScene(const char* name);
			RPGScenePTR CreatePlaybackIntroScene(const char* name);

			TimerPTR CreateTimer();

			/* NOT Owner. */
			Engine::SDLLibPTR sdl;
			// NOT Owner
			RPGApplicationPTR app;
			Engine::IFileLoaderPTR fileloader;
			AssetManagerPTR assetm;
			TimeManagerPTR timem;
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner */
			Debug::DebugPTR debug;
		};
	}
}
#endif