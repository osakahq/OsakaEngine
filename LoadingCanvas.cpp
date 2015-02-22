 #include "stdafx.h"
#include "Debug.h"
#include "Timer.h"
#include "EventArgs.h"
#include "EventHandler.h"
#include "Canvas.h"
#include "RPGApplication.h"
#include "LoadingCanvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		LoadingCanvas::LoadingCanvas(RPGApplicationPTR& app) : Canvas(app){
			isAnimating = false;
			beginSecondPart = false;
			alpha = 0;
			midAnimation = std::make_shared<Component::EventHandler>();
			endAnimation = std::make_shared<Component::EventHandler>();
		}
		LoadingCanvas::~LoadingCanvas(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingCanvas");
#endif
		}
		void LoadingCanvas::_delete(){
			Canvas::_delete();
			midAnimation = nullptr;
			endAnimation = nullptr;
			timer = nullptr;
		}
		void LoadingCanvas::Init(TimerPTR& timer){
			//this is called in factory
			this->timer = timer;
		}
		void LoadingCanvas::Load(){
			//this is called in rpg_bootstrap but not really needed.
		}
		void LoadingCanvas::Unload(){
			//unload not implemented
		}
		void LoadingCanvas::StartAnimation(TransitionType::Value type){
			this->type = type;
			isAnimating = true;
			timer->Start();
		}
		void LoadingCanvas::BeginEndAnimation(){
			beginSecondPart = true;
		}
		void LoadingCanvas::Show(){
			//when the scene is switched
		}
		void LoadingCanvas::Hide(){
			//when the scene is removed
		}
		void LoadingCanvas::StandBy(){
			//when a scene is stacked on top of this one
		}
		void LoadingCanvas::Focus(){
			//when a scene is removed and the next one is this one
		}

		void LoadingCanvas::Update(){
			
			if( isAnimating && timer->GetTicks() >= 1000 ){
				app->debug->l("[LoadingCanvas] 1 second");
				timer->Reset(1000);
			}
		}
		void LoadingCanvas::Draw(){
		}

		void LoadingCanvas::Reset(){
			//does nothing but is called when gamesessionmanager changes
		}
	}
}