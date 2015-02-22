 #include "stdafx.h"
#ifndef ENGINE_SDLLIB_H
#define ENGINE_SDLLIB_H
#include "engine_include.h"
#include "osaka_forward.h"
struct SDL_Window;
struct SDL_Renderer;

namespace Osaka{
	
	namespace Engine{
		
		class SDLLib{
		public:
			SDLLib(Debug::DebugPTR& debug);
			~SDLLib();
			void _delete();
			/* Creates all that is needed for a full functionality of SDL */
			void Init(const char* title, int window_width, int window_height, RGBA_HEX& render_color);
			bool Start();
			/* In rpg_bootstrap everything is loaded and texture class need a validr renderer,
			 * so instead of calling Start() inside EApplication, we just show the window */
			void ShowWindow();
			void ResetRender(RGBA_HEX render_color);
			void ResetRenderColor();
			void Clear();
			void Render();

			//These sound functions could be in their own class but they are fine in here.
			void PlayMusic(Mix_Music& music);
			void PauseMusic();
			void ResumeMusic();
			void StopMusic();
			void StopMusicFadeOut(int ms);
			void SetVolume(int volume, int channel = -1);
			void SetMusicVolume(int volume);

			/* Owner */
			SDL_Renderer* renderer;
		/* ----------------------------------------------------------------------------------- */
		private:
			std::string title;
			int window_width;
			int window_height;
			RGBA_HEX render_color;

			/* NOT owner */
			Debug::DebugPTR debug;

			/* OWNER */
			SDL_Window* window;
		};
	}
}
#endif