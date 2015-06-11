 #include "stdafx.h"
#ifndef RPGLIB_TIMEMANAGER_H
#define RPGLIB_TIMEMANAGER_H

namespace Osaka{
	namespace RPGLib{

		class TimeManager{
		public:
			TimeManager();
			~TimeManager();
			void _delete();

#ifdef _DEBUG
			/* This is to make the pausedtime go away. For more info go to RPGApplication.h/EApplication.h */
			void UpdateTicks(Uint32 pausedtime);
			/* We have to substract every single time when we call SDL_GetTicks */
			Uint32 accumulatedPausedTime;
#else
			//Updates the ticks
			void UpdateTicks();
#endif
			//Get the ticks for the timer
			Uint32 GetTicks();

			//See variable comment for more info.
			Uint32 GetDelta();
		private:
			/* If the call of UpdateTicks took longer than maxElapsedTime, it will cheat and make it look like it only passed `maxElapsedTime` time */
			const Uint32 maxElapsedTime;
			Uint32 ticks;

			/* This is the interval between frames. (Interval since the last Update). 
			 * This will include the delay time, so it will be always around 15ms/16ms when 60fps (vsync off) 
			 * If vsync is on, it will be almost every time 16ms */
			Uint32 delta;
			Uint32 oldTicks; //A helper var
		};
	}
}

#endif