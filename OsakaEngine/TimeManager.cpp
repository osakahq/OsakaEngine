 #include "stdafx.h"

#include "TimeManager.h"
namespace Osaka{
	namespace RPGLib{

		TimeManager::TimeManager(){
			/* Just in case */
			ticks = SDL_GetTicks();
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
	}
}