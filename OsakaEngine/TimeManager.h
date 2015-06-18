 #include "stdafx.h"
#ifndef RPGLIB_TIMEMANAGER_H
#define RPGLIB_TIMEMANAGER_H

namespace Osaka{
	namespace RPGLib{

		class TimeManager{
		public:
			TimeManager();
			~TimeManager();
			
			/* Delta value is handled by EApplication. */
			void Update(const Uint32 delta);
			
			//Get the ticks for the timer
			Uint32 GetTicks();

			//See variable comment for more info.
			Uint32 GetDelta();
		private:
			/* Ticks is incremented by delta. */
			Uint32 ticks;

			/* This is the interval between frames. (Interval since the last Update). 
			 * This will include the delay time, so it will be always around 15ms/16ms when 60fps (vsync off) 
			 * If vsync is on, it will be almost every time 16ms */
			Uint32 delta;
		};
	}
}

#endif