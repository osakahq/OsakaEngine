 #include "stdafx.h"
#ifndef RPGLIB_FACTORY_H
#define RPGLIB_FACTORY_H
#include "osaka_forward.h"
struct SDL_Renderer;

namespace Osaka{
	
	namespace RPGLib{
		
		class Factory{
		public:
			Factory(Debug::Debug* debug);
			~Factory();
			/* Check that the references are set */
			void Check();

			// Gives away ownership.
			Engine::Texture* CreateTexture();
			Engine::Sound* CreateSound(sound_data& data);
			// Scenes
			InitScene* CreateInitScene();
			
			Timer* CreateTimer();

			/* NOT Owner. */
			Engine::SDLLib* sdl;
			// NOT Owner
			RPGApplication* app;
			Engine::IFileLoader* fileloader;
			AssetManager* assetm;
			TimeManager* timem;
			TextureManager* texturem;
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner */
			Debug::Debug* debug;

		};
	}
}
#endif