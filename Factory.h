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
			void Check();

			// Gives away ownership.
			Engine::TexturePTR CreateTexture();
			Engine::SoundPTR CreateSound(sound_dataPTR& data);
			// Scenes
			InitScenePTR CreateInitScene();
			RPGScenePTR Factory::CreateLoadingScene(const char* name);
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

			/* Gives away ownership */
			UserInterfacePTR CreateDummyUI();
		};
	}
}
#endif