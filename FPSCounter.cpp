 #include "stdafx.h"

#include "engine_include.h"
#include "Debug.h"
#include "Timer.h"
#include "FontManager.h"
#include "FPSCounter.h"

namespace Osaka{
	namespace RPGLib{
		FPSCounter::FPSCounter(Debug::DebugPTR& debug, FontManagerPTR& font, int _target_fps) : target_fps(_target_fps)
#ifdef _DEBUG
			,show_sum_frames(true)
#else
			,show_sum_frames(false)
#endif
		{
			ticks = 0;
			this->font = font;
			frames = 0;
			this->debug = debug;
			sum_frame_ms = 0;
			calls = 0;
			//this->target_fps = target_fps;
		}
		FPSCounter::~FPSCounter(){

		}
		void FPSCounter::_delete(){
			font = nullptr;
			debug = nullptr;
		}
		
		void FPSCounter::Start(){
			debug->l("[FPSCounter] The first number is the FPS.");
			debug->l("[FPSCounter] The second number is the average time in milliseconds per frame when " + std::to_string(target_fps) + " frames have passed.");
			debug->l("[FPSCounter] The second number INCLUDES `sdl->Present()`");
			ticks = SDL_GetTicks();
		}
		
		void FPSCounter::BeforePresent(){
			if( show_sum_frames ){
				//show_sum_frames is a constant
				if( calls == target_fps ){
					//Only when _DEBUG
					average_frame_ms = std::to_string( sum_frame_ms / calls );
					sum_frame_ms = 0;
					calls = 0;
				}

				font->RenderTextLine(average_frame_ms, 5, 20);
			}
			
			frames++;
			Uint32 time = SDL_GetTicks() - ticks;
			if( time >= 1000 ){
				ticks = SDL_GetTicks() - (time-1000);
				current_fps = std::to_string(frames);
				frames = 0;
				
				if( time > 1020 ){
					//In a fast normal operation, the difference between time-1000 will be minimal.
					//If the application is starting to slow, make sure to announce that BeforePresent was called late
					debug->l("[FPS] FPSCounter was called very late: " + std::to_string(time));
				}
			}
			font->RenderTextLine(current_fps, 5, 5);
		}

		/* This function is only called when _DEBUG. Because it is after RenderPresent */
		void FPSCounter::AfterPresent(Uint32 frame_ms){
			sum_frame_ms += frame_ms;
			++calls;
		}
	}
}