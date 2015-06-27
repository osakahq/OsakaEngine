 #include "stdafx.h"

#ifdef _DEBUG
	#include <Psapi.h>
#endif
#include "ConsoleColors.h"
#include "Hiccups.h"
#include "StaticText.h"
#include "engine_include.h"
#include "Debug.h"
#include "FontManager.h"
#include "FPSCounter.h"

#define FPSCOUNTER_CAPTIMER 3000

namespace Osaka{
	namespace RPGLib{
		FPSCounter::FPSCounter(int _target_fps, int _space_x, int _space_y, const bool _show_sum_frames) 
			: target_fps(_target_fps), space_x(_space_x*4), space_y(_space_y), show_sum_frames(_show_sum_frames)


		{
			ticks = 0;
			frames = 0;
			sum_frame_ms = 0;
			calls = 0;
			//this->target_fps = target_fps;

			seconds = FPSCOUNTER_SECONDS_RAM;
			
			hiccups = new Hiccups();
			stext_ram = NULL;
			stext_fps = NULL;
			stext_avg = NULL;
			font = NULL;
			debug = NULL;

			average_frame_ms[0] = '\0';
			current_fps[0] = '\0';
			usedMB[0] = '\0';
		}
		FPSCounter::~FPSCounter(){
			font = NULL;
			debug = NULL;
			delete hiccups; hiccups = NULL;
			delete stext_ram; stext_ram = NULL;
			delete stext_fps; stext_fps = NULL;
			delete stext_avg; stext_avg = NULL;
		}
		
		void FPSCounter::Init(Debug::Debug* debug, FontManager* font){
			this->font = font;
			this->debug = debug;
		}
		void FPSCounter::Start(){
			MULTIPLE_LOG_START("[FPSCounter] Indicator FPS: How many frames have passed in 1 second.\n");
			MULTIPLE_LOG("[FPSCounter] Indicator Average: Average of how long %d frames took to render without SDL_Delay.\n", target_fps);
			MULTIPLE_LOG("[FPSCounter] Indicator Delta: If delta is greater than %d.\n", target_fps);
			MULTIPLE_LOG_END("[FPSCounter] Indicator Hiccups: Reports if the times of frames take longer than the mean(average) in sets of %d\n", target_fps);
			
			stext_fps = font->CreateStaticText("fps", 5, 5, 3);
			stext_avg = font->CreateStaticText("avg", 5, space_y + 5, 3);
			stext_ram = font->CreateStaticText("ram", 5, space_y + 20, 3);
			ticks = SDL_GetTicks();
		}
		
		void FPSCounter::BeforePresent(){
			if( show_sum_frames ){
				//show_sum_frames is a constant
				if( calls == target_fps ){
					float avr = static_cast<float>(sum_frame_ms) / calls;
					sprintf_s(average_frame_ms, "%.3f", avr);
					hiccups->EndSet(avr);
					sum_frame_ms = 0;
					calls = 0;
				}
				stext_avg->Render();
				font->RenderTextLine(average_frame_ms, space_x, space_y+5);
			}
			
			Uint32 time = SDL_GetTicks();
			Uint32 diff = time - ticks;
			if( diff >= 1000 ){
				/* Because we aren't resetting the `ticks`, if diff is more than 3 seconds, then cap it. Why? So it catches up faster. */
				if( diff > FPSCOUNTER_CAPTIMER ){
					diff = FPSCOUNTER_CAPTIMER;
				}
				ticks = time - (diff-1000);
				sprintf_s(current_fps, "%d", frames);
				frames = 0;
#ifdef _DEBUG
				if( diff > 1017 ){
					//In a fast normal operation, the difference between time-1000 will be minimal.
					//If the application is starting to slow, make sure to announce that BeforePresent was called late
					LOG("[FPSCounter] BeforePresent() was called very late: %d\n", diff);
				}

				//First increments then grabs value.
				if( ++seconds >= FPSCOUNTER_SECONDS_RAM ){
					PROCESS_MEMORY_COUNTERS_EX pmc;
					if( GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)) ){
						sprintf_s(usedMB, "%.2f|%.2f", (static_cast<float>(pmc.PrivateUsage)/1024)/1024, (static_cast<float>(pmc.WorkingSetSize)/1024)/1024);
						current_dot = 11; //11 slot is \0
					}else{
						sprintf_s(usedMB, "%s", "error");
						current_dot = 6; //6 slot is \0
						LOG("[FPSCounter] ERROR! GetProcessMemoryInfo returned false.\n");
					}
					seconds = 0;
				}
				if( seconds > 0 && seconds % 3 == 0 ){
					usedMB[current_dot] = '.';
					usedMB[++current_dot] = '\0'; //first increments, then grabs value
				}
#endif
			}
			stext_fps->Render();
			font->RenderTextLine(current_fps, space_x, 5);

#ifdef _DEBUG
			stext_ram->Render();
			font->RenderTextLine(usedMB, space_x,space_y+20);
#endif
		}

		/* This is only called if `show_fpscounter` (in RPGApplication) is true */
		void FPSCounter::AfterPresent(Uint32 started){
			++frames;
			if( show_sum_frames ){
				started = SDL_GetTicks() - started;
				sum_frame_ms += started;
				++calls;
				hiccups->Frame(started);
			}
		}
	}
}