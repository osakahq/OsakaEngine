 #include "stdafx.h"

#include "TimeManager.h"
namespace Osaka{
	namespace RPGLib{

		TimeManager::TimeManager(){
			ticks = 0;
			delta = 0;
		}
		TimeManager::~TimeManager(){

		}
		
		void TimeManager::Update(const Uint32 delta){
			ticks += delta;
			this->delta = delta;
		}
		Uint32 TimeManager::GetTicks(){
			return ticks;
		}
		Uint32 TimeManager::GetDelta(){
			return delta;
		}
	}
}