 #include "stdafx.h"

#include "engine_include.h"
#include "Debug.h"
#include "Timer.h"
#include "FontManager.h"
#include "FPSCounter.h"

namespace Osaka{
	namespace RPGLib{
		FPSCounter::FPSCounter(Debug::DebugPTR& debug, TimerPTR& timer, FontManagerPTR& font, int _target_fps) : target_fps(_target_fps){
			this->timer = timer;
			this->font = font;
			frames = 0;
			this->debug = debug;
			//this->target_fps = target_fps;
		}
		FPSCounter::~FPSCounter(){

		}
		void FPSCounter::_delete(){
			timer = nullptr;
			font = nullptr;
			debug = nullptr;
		}
		
		void FPSCounter::Start(){
			timer->Start();
		}
		void FPSCounter::EndOfFrame(){
			font->RenderTextMultiple("HOLA HOLA HOLA HOLA HOLA WTFASDASD", 50, 50, 10);
			frames++;
			if( timer->GetTicks() >= 1000 ){
				current_fps = std::to_string(frames);
				timer->Reset(1000);
				if( frames < target_fps ){
					debug->l("[FPSCounter] Frames rendered in the past second: " + std::to_string(frames));
				}
				frames = 0;
			}
			font->RenderTextLine(current_fps, 5, 5);
		}
	}
}