 #include "stdafx.h"

#ifndef RPGLIB_FPSCOUNTER_H
#define RPGLIB_FPSCOUNTER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{

		class FPSCounter{
		public:
			FPSCounter(Debug::DebugPTR& debug, FontManagerPTR& font, int target_fps);
			~FPSCounter();
			void _delete();
			/* This is called before EApplication::Run() (in RPGApplication, right outside the loop) */
			void Start();
			/* This is called after the draw loop and before SDL_Present and before manual cap (if vsync is on) */
			void EndOfFrame();

			/* Only called when _DEBUG */
			void EndOfLoop(Uint32 frame_ms);
		private:
			/* NOT Owner */
			Debug::DebugPTR debug;
			/* NOT Owner */
			FontManagerPTR font;

			/* For every second, show the counted frames */
			Uint32 ticks;

			std::string current_fps;

			const int target_fps;
			int frames;

			/* Only when _DEBUG. Everytime the loop ends (after Present), we count the frame ms */
			const bool show_sum_frames;
			Uint32 sum_frame_ms;
			std::string average_frame_ms;
		};
	}
}

#endif