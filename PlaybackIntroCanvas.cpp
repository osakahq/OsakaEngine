 #include "stdafx.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Debug.h"
#include "Timer.h"
#include "EventArgs.h"
#include "EventHandler.h"
#include "Canvas.h"
#include "RPGApplication.h"
#include "Utils.h"
#include "PlaybackIntroCanvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		PlaybackIntroCanvas::PlaybackIntroCanvas(RPGApplicationPTR& app) : Canvas(app){
			
		}
		PlaybackIntroCanvas::~PlaybackIntroCanvas(){

		}
		void PlaybackIntroCanvas::_delete(){
			
		}
		void PlaybackIntroCanvas::Init(){
			
		}
		void PlaybackIntroCanvas::Load(){
			//this is called in rpg_bootstrap but not really needed.
		}
		void PlaybackIntroCanvas::Unload(){
			//unload not implemented
		}
		
		void PlaybackIntroCanvas::Show(){
			//when the scene is switched
		}
		void PlaybackIntroCanvas::Hide(){
			//when the scene is removed
		}
		void PlaybackIntroCanvas::StandBy(){
			//when a scene is stacked on top of this one
		}
		void PlaybackIntroCanvas::Focus(){
			//when a scene is removed and the next one is this one
		}

		void PlaybackIntroCanvas::Update(){
			
		}
		void PlaybackIntroCanvas::Draw(){
			
		}

		void PlaybackIntroCanvas::Reset(){
			//does nothing but is called when gamesessionmanager changes
		}
	}
}