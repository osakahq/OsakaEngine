 #include "stdafx.h"

#ifndef RPGLIB_FPSCOUNTER_H
#define RPGLIB_FPSCOUNTER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{

		class FPSCounter{
		public:
			FPSCounter(Debug::DebugPTR& debug, FontManagerPTR& font, int target_fps, int _space_x, int _space_y);
			~FPSCounter();
			void _delete();
			/* This is called before EApplication::Run() (in RPGApplication, right outside the loop) */
			void Start();
			/* This is called after the draw loop and before SDL_Present and before manual cap (if vsync is on) */
			void BeforePresent();

			/* Only called when _DEBUG */
			void AfterPresent(const Uint32 frame_ms);
		private:
			/* Prints in console if a frame(s) took longer than the rest of the frames */
			Hiccups* hiccups; //It's okay to use raw pointer. The only class using it is this one.

			/* NOT Owner */
			Debug::DebugPTR debug;
			/* NOT Owner */
			FontManagerPTR font;

			/* For every second, show the counted frames */
			Uint32 ticks;

			/* The space for each character in the fontmap */
			const int space_x;
			const int space_y;
			
			std::string current_fps;

			const int target_fps;
			int frames;

			/* Only when _DEBUG. Everytime the loop ends (after Present), we count the frame ms */
			const bool show_sum_frames;
			Uint32 sum_frame_ms;
			std::string average_frame_ms;
			/* We need to make sure that average ms frames is perfect. That is why we need a separate variable (from frames) */
			int calls;

			//Text for FPS and AVG
			/* Owner */
			StaticTextPTR stext_fps;
			/* Owner */
			StaticTextPTR stext_avg;
		};
	}
}

#endif