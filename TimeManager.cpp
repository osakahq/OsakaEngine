 #include "stdafx.h"

#include "TimeManager.h"
namespace Osaka{
	namespace RPGLib{

		TimeManager::TimeManager(){
			/* Just in case */
			ticks = SDL_GetTicks();
		}
		TimeManager::~TimeManager(){
#ifdef _DEBUG
			_CHECKDELETE("TimeManager");
#endif
		}
		void TimeManager::_delete(){

		}
		void TimeManager::UpdateTicks(){
			/* This is called every update (from RPGApplication::Update()) */
			ticks = SDL_GetTicks();
		}
		
		Uint32 TimeManager::GetTicks(){
			return ticks;
		}
	}
}