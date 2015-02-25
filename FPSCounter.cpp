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

			//this->target_fps = target_fps;
		}
		FPSCounter::~FPSCounter(){

		}
		void FPSCounter::_delete(){
			font = nullptr;
			debug = nullptr;
		}
		
		void FPSCounter::Start(){
			ticks = SDL_GetTicks();
		}
		
		void FPSCounter::EndOfFrame(){

			frames++;
			Uint32 time = SDL_GetTicks() - ticks;
			if( time >= 1000 ){
				current_fps = std::to_string(frames);

				ticks = SDL_GetTicks() - (time-1000);

				if( frames < target_fps ){
					debug->l("[FPSCounter] Frames rendered in the past second: " + std::to_string(frames));
				}

				if( show_sum_frames ){
					//Only when _DEBUG
					average_frame_ms = std::to_string( (static_cast<float>(sum_frame_ms)) / frames);
					sum_frame_ms = 0;
				}
				frames = 0;
			}
			font->RenderTextLine(current_fps, 5, 5);

			if( show_sum_frames ){
				//Because it is constant, there will be no problem with branch
				font->RenderTextLine(average_frame_ms, 5, 20);
			}
		}

		/* This function is only called when _DEBUG. Because it is after RenderPresent */
		void FPSCounter::EndOfLoop(Uint32 frame_ms){
			sum_frame_ms += frame_ms;
		}
	}
}