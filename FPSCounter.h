 #include "stdafx.h"

#ifndef RPGLIB_FPSCOUNTER_H
#define RPGLIB_FPSCOUNTER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{

		class FPSCounter{
		public:
			FPSCounter(Debug::DebugPTR& debug, TimerPTR& timer, FontManagerPTR& font, int target_fps);
			~FPSCounter();
			void _delete();
			/* This is called before EApplication::Run() (in RPGApplication, right outside the loop) */
			void Start();
			/* This is called after the draw loop and before SDL_Present and before manual cap (if vsync is on) */
			void EndOfFrame();
		private:
			/* NOT Owner */
			Debug::DebugPTR debug;
			/* NOT Owner */
			TimerPTR timer;
			/* NOT Owner */
			FontManagerPTR font;

			std::string current_fps;

			const int target_fps;
			int frames;
		};
	}
}

#endif