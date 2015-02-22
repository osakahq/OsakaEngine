#include "stdafx.h"
#include "Debug.h"
#include "SDLLib.h"

namespace Osaka{
	namespace Engine{

		SDLLib::SDLLib(Debug::DebugPTR& debug){
			this->debug = debug;
			window = NULL;
			renderer = NULL;
		}
		SDLLib::~SDLLib(){
#ifdef _DEBUG
			_CHECKDELETE("SDLLib");
#endif
			Mix_HaltMusic();
			Mix_HaltChannel(-1); //-1 for all channels

			if( window != NULL )
				SDL_DestroyWindow(window);
			if( renderer != NULL )
				SDL_DestroyRenderer(renderer);
				
			window = NULL;
			renderer = NULL;
	
			Mix_Quit();
			IMG_Quit();
			SDL_Quit();
		}
		void SDLLib::_delete(){
			debug = nullptr;
		}
		void SDLLib::ResetRender(RGBA_HEX render_color){
			SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
		}
		void SDLLib::ResetRenderColor(){
			SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
		}
		void SDLLib::Clear(){
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
		}
		void SDLLib::Render(){
			SDL_RenderPresent(renderer);
		}

		void SDLLib::Init(const char* title, int window_width, int window_height, RGBA_HEX& render_color){
			this->title = title;
			this->window_width = window_width;
			this->window_height = window_height;

			this->render_color = render_color;
		}
		void SDLLib::ShowWindow(){
			SDL_ShowWindow(window);
		}
		
		bool SDLLib::Start(){
			
			if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ){
				debug->l((std::string("[SDLLib] SDL could not initialize! SDL_Error: ")+SDL_GetError()).c_str() );
				return false;
			}
			//Set texture filtering to linear
			if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ){
				debug->l("[SDLLib] Warning: Linear texture filtering not enabled.");
			}

			window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_HIDDEN );
			if( window == NULL ){
				debug->l(std::string("[SDLLib] Window could not be created! SDL_Error: ")+SDL_GetError());
				return false;
			}
			
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if( renderer == NULL ){
				debug->l(std::string("[SDLLib] Renderer could not be created. SDL Error: ") + SDL_GetError());
				return false;
			}
				
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !(IMG_Init(imgFlags) & imgFlags)){
				debug->l((std::string("[SDLLib] IMG_Init error! IMG_Error: ")+IMG_GetError()).c_str());
				return false;
			}else{
				//Success
					
			}

			/*if( TTF_Init() == -1 ){
				printf("TTF_Init error! TTF_Error: %s\n", TTF_GetError() );
				success = false;
			}else{
				SDLMain::Font = TTF_OpenFont("..\\test-sdl\\font.ttf", 12);
				if( Font == NULL ){
					printf("Failed to open font.tff. TTF_Error: %s\n", TTF_GetError());
				}
			}*/

			if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ){
				debug->l(std::string("[SDLLib] SDL_mixer could not initialize. SDL_mixer error: ") + Mix_GetError());
				//return false;
			}
				
			return true;
		}

		//---------------------------------------------------------------------------------------
		void SDLLib::PlayMusic(Mix_Music& music){
			Mix_PlayMusic(&music, -1);
		}
		void SDLLib::SetVolume(int volume, int channel){
			Mix_Volume(channel, volume);
		}
		void SDLLib::SetMusicVolume(int volume){
			Mix_VolumeMusic(volume);
		}
		void SDLLib::PauseMusic(){
			Mix_PauseMusic();
		}
		void SDLLib::ResumeMusic(){
			Mix_ResumeMusic();
		}
		void SDLLib::StopMusic(){
			Mix_HaltMusic();
		}
		void SDLLib::StopMusicFadeOut(int ms){
			Mix_FadeOutMusic(ms);
		}
	}
}