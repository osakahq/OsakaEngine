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

			//Updates the ticks
			void UpdateTicks();
			//Get the ticks for the timer
			Uint32 GetTicks();
		private:
			Uint32 ticks;
		};
	}
}

#endif