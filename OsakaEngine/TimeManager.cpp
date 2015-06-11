 #include "stdafx.h"

#include "TimeManager.h"
namespace Osaka{
	namespace RPGLib{

		TimeManager::TimeManager() : maxElapsedTime(120){
			/* Just in case */
			ticks = SDL_GetTicks();
			oldTicks = ticks;

			//TODO: this default value should come from the data.xml (target ms per frame)
			delta = 16;
#ifdef _DEBUG
			accumulatedPausedTime = 0;
#endif
		}
		TimeManager::~TimeManager(){
#ifdef _DEBUG
			_CHECKDELETE("TimeManager");
#endif
		}
		void TimeManager::_delete(){

		}
		
#ifdef _DEBUG
		void TimeManager::UpdateTicks(Uint32 pausedtime){
			//For info go to header
			accumulatedPausedTime += pausedtime;
			ticks = SDL_GetTicks() - accumulatedPausedTime;

			//In a perfect scenario (60 fps) delta should always be 16ms
			delta = ticks - oldTicks;
			if( delta > maxElapsedTime ){
				//Because the frame took longer than `maxElapsedTime`, we have to make it look it never happened (but leave `maxElapsedTime` time)
				//So, if the interval took 3000ms, then we substract 3000 - 120 so that, makes it look only 120ms have elapsed.
				accumulatedPausedTime += (delta - maxElapsedTime);
				ticks -= (delta - maxElapsedTime);

				//This is easier: we just truncate the value, make it look it only passed `maxElapsedTime`
				delta = maxElapsedTime;
			}
			oldTicks = ticks;
		}
#else
		void TimeManager::UpdateTicks(){
			/* This is called every update (from RPGApplication::Update()) */
			ticks = SDL_GetTicks();
		}
#endif
		
		Uint32 TimeManager::GetTicks(){
			return ticks;
		}
		Uint32 TimeManager::GetDelta(){
			return delta;
		}
	}
}