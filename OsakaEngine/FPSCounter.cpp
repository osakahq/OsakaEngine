 #include "stdafx.h"

#include "Hiccups.h"
#include "StaticText.h"
#include "engine_include.h"
#include "Debug.h"
#include "Timer.h"
#include "FontManager.h"
#include "FPSCounter.h"

namespace Osaka{
	namespace RPGLib{
		FPSCounter::FPSCounter(Debug::DebugPTR& debug, FontManagerPTR& font, int _target_fps, int _space_x, int _space_y) 
			: target_fps(_target_fps), space_x(_space_x*4), space_y(_space_y)
#ifdef OSAKA_SHOWAVERAGEFPS
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

			hiccups = new Hiccups();
		}
		FPSCounter::~FPSCounter(){
			delete hiccups;
		}
		void FPSCounter::_delete(){
			font = nullptr;
			debug = nullptr;

			stext_fps->_delete(); stext_fps = nullptr;
			stext_avg->_delete(); stext_avg = nullptr;
		}
		
		void FPSCounter::Start(){
			debug->l("[FPSCounter] Indicator FPS: How many frames have passed in 1 second.");
			debug->l("[FPSCounter] Indicator Average: Average time in " + std::to_string(target_fps) + " frames.");
			debug->l("[FPSCounter] Indicator Hiccups: Reports if the times of frames take longer than the mean(average) in sets of " + std::to_string(target_fps));
			ticks = SDL_GetTicks();

			stext_fps = font->CreateStaticText("fps", 5, 5, 3);
			stext_avg = font->CreateStaticText("avg", 5, space_y + 5, 3);
		}
		
		void FPSCounter::BeforePresent(){
			if( show_sum_frames ){
				//show_sum_frames is a constant
				if( calls == target_fps ){
					//Only when _DEBUG
					float avr = static_cast<float>(sum_frame_ms) / calls;
					average_frame_ms = std::to_string(avr);
					hiccups->EndSet(avr);
					sum_frame_ms = 0;
					calls = 0;
				}
				stext_avg->Render();
				font->RenderTextLine(average_frame_ms, space_x, space_y+5);
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
					debug->l("[FPSCounter] BeforePresent() was called very late: " + std::to_string(time));
				}
			}
			stext_fps->Render();
			font->RenderTextLine(current_fps, space_x, 5);
		}

		/* This function is only called when _DEBUG. Because it is after RenderPresent */
		void FPSCounter::AfterPresent(const Uint32 frame_ms){
			sum_frame_ms += frame_ms;
			++calls;
			hiccups->Frame(frame_ms);
		}
	}
}