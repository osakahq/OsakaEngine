 #include "stdafx.h"

#include "TimeManager.h"
#include "Timer.h"
namespace Osaka{
	namespace RPGLib{

		Timer::Timer(TimeManager* timem){
			this->timem = timem;

			mStartTicks = 0;
			mPausedTicks = 0;

			mPaused = false;
			mStarted = false;
		}
		Timer::~Timer(){
#ifdef _DEBUG
			_CHECKDELETE("Timer");
#endif
			timem= NULL;
		}
		
		void Timer::Start(){
			mStarted = true;
			mPaused = false;

			//Cuando se empieza, se guarda cuando empezo
			mStartTicks = timem->GetTicks();
			mPausedTicks = 0;
		}

		void Timer::Reset(){
			Timer::Reset(0);
		}

		void Timer::Reset(Uint32 add){
			mStarted = true;
			mPaused = false;

			//For example, time = every second.  GetTicks (1200ms) - 1000ms
			//We need to rest 200ms, so we can catch up
			add = this->GetTicks() - add;
			
			mStartTicks = timem->GetTicks() - add;
			mPausedTicks = 0;
		}

		void Timer::Stop(){
			mStarted = false;
			mPaused = false;

			mStartTicks = 0;
			mPausedTicks = 0;
		}

		void Timer::Pause(){
			if( mStarted && !mPaused ){
				mPaused = true;
				//Cuando se hace pause, se obtiene los milisegundos absolutos (no relativos)
				mPausedTicks = timem->GetTicks() - mStartTicks;
				mStartTicks = 0;
			}
		}

		//Unpause es lo mismo que start, pero hace la resta para sumar los milisegundos
		//Empeze a 10ms
		//Hice pause a 25ms, tengo 15ms absolutos
		//Hice unpause a 50ms, empiezo a 50ms y necesito agregarle los 15ms, entonces hago "trampa" y le digo que empeze a 35ms(50ms-15ms) (sumando los 15ms)
		void Timer::Unpause(){
			if( mStarted && mPaused ){
				mPaused = false;
				//Cuando se hace unpause se hace reset y de ese reset se le restan para ""sumar"" los milisegundos que tiene mPausedTicks, esto quiere decir que
				//mStartTicks = SDL_GetTicks() -> empiezo desde estos milisegunos (como si fuera start())
				//Y solamente falta agregar los milisegundos que ya tenemos, le restamos los milisegundos absolutos (mPausedTicks)
		
				mStartTicks = timem->GetTicks() - mPausedTicks;
				mPausedTicks = 0;
			}
		}

		Uint32 Timer::GetTicks(){
	
			if(mStarted){
				if( mPaused ){
					return mPausedTicks;
				}else{
					//mStartTicks siempre tiene los milisegundos que empezo, ya sea desde que se hace start o unpause (start - los milisegundos que llevo)
					return timem->GetTicks() - mStartTicks;
				}
			}
			return 0;
		}

		Uint32 Timer::GetTotalTicks(){
			return timem->GetTicks();
		}

		bool Timer::IsPaused(){
			return mPaused && mStarted;
		}
		bool Timer::IsStarted(){
			return mStarted;
		}
		
	}
}