 #include "stdafx.h"
#ifndef TIME_TIMER_H
#define TIME_TIMER_H

#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class Timer{
		public:
			Timer(TimeManager* timem);
			~Timer();
			
			void Start();
			void Stop();
			void Pause();
			void Unpause();

			/* This is the reset function to call, because it won't neglect the ticks (See the function) 
			 * `time` is the ms that you wait. For example, if you want a trigger every 1 second, then you put 1000 in the parameter */
			void Reset(Uint32 add);
			void Reset();

			Uint32 GetTicks();
			Uint32 GetTotalTicks();

			bool IsPaused();
			bool IsStarted();
		private:
			/* NOT Owner. */
			TimeManager* timem;

			Uint32 mStartTicks;
			Uint32 mPausedTicks;

			bool mPaused;
			bool mStarted;
		};
	}
}

#endif