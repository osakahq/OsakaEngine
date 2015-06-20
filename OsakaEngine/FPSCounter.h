 #include "stdafx.h"

#ifndef RPGLIB_FPSCOUNTER_H
#define RPGLIB_FPSCOUNTER_H

#define FPSCOUNTER_SECONDS_RAM 12

#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{

		class FPSCounter{
		public:
			FPSCounter(int target_fps, int _space_x, int _space_y, const bool _show_sum_frames);
			~FPSCounter();
			void Init(Debug::Debug* debug, FontManager* font);
			
			/* This is called before EApplication::Run() (in RPGApplication, right outside the loop) */
			void Start();
			/* This is called after the draw loop and before SDL_Present and before manual cap (if vsync is on) */
			void BeforePresent();

			/* Only called when _DEBUG */
			void AfterPresent(Uint32 started);
		private:
			/* Prints in console if a frame(s) took longer than the rest of the frames */
			Hiccups* hiccups; //It's okay to use raw pointer. The only class using it is this one.

			/* NOT Owner */
			Debug::Debug* debug;
			/* NOT Owner */
			FontManager* font;

			/* For every second, show the counted frames */
			Uint32 ticks;

			/* The space for each character in the fontmap */
			const int space_x;
			const int space_y;
			
			std::string current_fps;

			const int target_fps;
			int frames;

			/* If true everytime the loop ends (after Present), we count the frame ms */
			const bool show_sum_frames;
			Uint32 sum_frame_ms;
			std::string average_frame_ms;
			/* We need to make sure that average ms frames is perfect. That is why we need a separate variable (from frames) */
			int calls;

			//Text for FPS and AVG
			/* Owner */
			StaticText* stext_fps;
			/* Owner */
			StaticText* stext_avg;

			/* Owner */
			StaticText* stext_ram;
			std::string usedMB;
			/* Every FPSCOUNTER_SECONDS_RAM seconds it will update */
			int seconds;
		};
	}
}

#endif