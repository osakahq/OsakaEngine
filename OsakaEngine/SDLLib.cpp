#include "stdafx.h"
#include "Debug.h"
#include "SDLLib.h"

void _SDLLib_Log(void* userdata, int category, SDL_LogPriority priority, const char* message) { 
	LOG("[SDLLib] Log: %s\n", message);
} 

namespace Osaka{
	namespace Engine{

		SDLLib::SDLLib(Debug::Debug* debug){
			this->debug = debug;
			window = NULL;
			renderer = NULL;

			vsync = true;
		}
		SDLLib::~SDLLib(){
			debug = NULL;
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
		
		SDL_Renderer* SDLLib::GetRAWSDLRenderer(){
			if( renderer == NULL ){
				debug->e("[SDLLib] GetRAWSDLRenderer > texture is NULL");
			}
			//Doesn't give away ownership
			return renderer;
		}
		void SDLLib::SetRenderColor(RGBA_HEX& render_color){
			SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
		}
		void SDLLib::ResetRenderColor(){
			SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
		}
		void SDLLib::Clear(){
			SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
			SDL_RenderClear(renderer);
		}
		void SDLLib::Present(){
			SDL_RenderPresent(renderer);
		}

		void SDLLib::Init(const char* title, int window_width, int window_height, RGBA_HEX& render_color, bool vsync){
			this->title = title;
			this->window_width = window_width;
			this->window_height = window_height;

			this->vsync = vsync;
			this->render_color = render_color;
		}
		void SDLLib::ShowWindow(){
			SDL_ShowWindow(window);
		}
		
		bool SDLLib::Start(){
			SDL_LogSetOutputFunction(_SDLLib_Log, NULL);
			SDL_LogDebug(1, "SDL Log set to _SDLLib_Log");

			if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ){
				LOG("[SDLLib] SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
				return false;
			}
			//Set texture filtering to linear
			if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ){
				LOG("[SDLLib] Warning: Linear texture filtering not enabled.\n");
			}

#ifdef _DEBUG
			//So i can have the console and press f1 and see the whole window.
			window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 530, window_width, window_height, SDL_WINDOW_HIDDEN );
#else
			window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_HIDDEN );
#endif
			if( window == NULL ){
				LOG("[SDLLib] Window could not be created! SDL_Error: %s\n", SDL_GetError());
				return false;
			}
			Uint32 flag = SDL_RENDERER_ACCELERATED;
			if( vsync ){
				LOG("[SDLLib] VSync On\n");
				flag |= SDL_RENDERER_PRESENTVSYNC;
			}
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, flag);
			if( renderer == NULL ){
				LOG("[SDLLib] Renderer could not be created. SDL Error: %s\n", SDL_GetError());
				return false;
			}
				
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !(IMG_Init(imgFlags) & imgFlags)){
				LOG("[SDLLib] IMG_Init error! IMG_Error: %s\n", IMG_GetError());
				return false;
			}else{
				//Success
					
			}

			/*if( TTF_Init() == -1 ){
				LOG("TTF_Init error! TTF_Error: %s\n", TTF_GetError() );
				success = false;
			}else{
				SDLMain::Font = TTF_OpenFont("..\\test-sdl\\font.ttf", 12);
				if( Font == NULL ){
					LOG("Failed to open font.tff. TTF_Error: %s\n", TTF_GetError());
				}
			}*/

			//chunk size is 1024 because there is only 1ms of lag when playing a song
			if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0 ){
				LOG("[SDLLib] SDL_mixer could not initialize. SDL_mixer error: %s\n", Mix_GetError());
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