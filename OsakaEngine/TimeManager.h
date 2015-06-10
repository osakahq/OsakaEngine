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
		private:
			Uint32 ticks;
		};
	}
}

#endif