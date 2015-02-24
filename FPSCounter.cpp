 #include "stdafx.h"

#include "engine_include.h"
#include "Timer.h"
#include "FontManager.h"
#include "FPSCounter.h"

namespace Osaka{
	namespace RPGLib{
		FPSCounter::FPSCounter(TimerPTR& timer, FontManagerPTR& font, int _target_fps) : target_fps(_target_fps){
			this->timer = timer;
			this->font = font;
			frames = 0;
			//this->target_fps = target_fps;
		}
		FPSCounter::~FPSCounter(){

		}
		void FPSCounter::_delete(){
			timer = nullptr;
			font = nullptr;
		}
		
		void FPSCounter::Start(){
			timer->Start();
		}
		void FPSCounter::EndOfFrame(){
			Engine::render_info info = {
				10, 10, 0, NULL, SDL_FLIP_NONE
			};
			

			font->RenderText(std::string("HOLA"), info);
			frames++;
			if( timer->GetTicks() >= 1000 ){
				timer->Reset(1000);
				if( frames < target_fps ){
					printf("TEST SLOW! frames per second: %d\n", frames);
				}
				frames = 0;
			}
		}
	}
}