 #include "stdafx.h"
#include "GameDataParams.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Debug.h"
#include "Timer.h"
#include "EventArgs.h"
#include "EventHandler.h"
#include "Image.h"
#include "Canvas.h"
#include "Utils.h"
#include "RPGFactory.h"
#include "PlaybackIntroCanvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		PlaybackIntroCanvas::PlaybackIntroCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler) : Canvas(raw_renderer, ruler){
			this->engine_logo = nullptr;
			this->gamestudio_logo = nullptr;
		}
		PlaybackIntroCanvas::~PlaybackIntroCanvas(){

		}
		void PlaybackIntroCanvas::Load(RPGFactoryPTR& factory){
			//This will only called once because of the asset_loading_type (and the fact that there is no implementation of unload)
			engine_logo = factory->CreateImage(factory->gamedataparams->engine_logo);
			gamestudio_logo = factory->CreateImage(factory->gamedataparams->gamestudio_logo);
		}
		void PlaybackIntroCanvas::Unload(){
			//Just an example. This function will never be called (for now)
			this->engine_logo = nullptr;
			this->gamestudio_logo = nullptr;
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