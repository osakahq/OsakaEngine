 #include "stdafx.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Debug.h"
#include "Timer.h"
#include "EventArgs.h"
#include "EventHandler.h"
#include "Canvas.h"
#include "Utils.h"
#include "PlaybackIntroCanvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		PlaybackIntroCanvas::PlaybackIntroCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler) : Canvas(raw_renderer, ruler){
			
		}
		PlaybackIntroCanvas::~PlaybackIntroCanvas(){

		}
		void PlaybackIntroCanvas::_delete(){
			Canvas::_delete();
		}
		void PlaybackIntroCanvas::Update(){
		}
		void PlaybackIntroCanvas::Draw(){
		}
	}
}