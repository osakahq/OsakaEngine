 #include "stdafx.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Debug.h"
#include "Timer.h"
#include "EventArgs.h"
#include "EventHandler.h"
#include "Image.h"
#include "Canvas.h"
#include "Utils.h"
#include "PlaybackIntroCanvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		PlaybackIntroCanvas::PlaybackIntroCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler, ImagePTR& engine_logo, ImagePTR& gamestudio_logo) : Canvas(raw_renderer, ruler){
			this->engine_logo = engine_logo;
			this->gamestudio_logo = gamestudio_logo;
		}
		PlaybackIntroCanvas::~PlaybackIntroCanvas(){

		}
		void PlaybackIntroCanvas::_delete(){
			engine_logo = nullptr;
			gamestudio_logo = nullptr;
			Canvas::_delete();
		}
		void PlaybackIntroCanvas::Update(){
			engine_logo->Update();
		}
		void PlaybackIntroCanvas::Draw(){
			engine_logo->Draw();
		}
	}
}