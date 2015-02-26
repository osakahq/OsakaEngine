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
#include "LoadingCanvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		LoadingCanvas::LoadingCanvas(RPGApplicationPTR& app) : Canvas(app){
			isAnimating = false;
			skipUpdate = false;
			beginSecondPart = false;
			onMidAnimation = false;
			midAnimation = std::make_shared<Component::EventHandler>();
			endAnimation = std::make_shared<Component::EventHandler>();

			color.r = 0;
			color.g = 0;
			color.b = 0;
			color.a = 0;

			carp.x = app->ruler->x_top_left_corner;
			carp.y = app->ruler->y_top_left_corner;
			carp.w = app->ruler->max_width;
			carp.h = app->ruler->max_height;
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
			beginSecondPart = false;
			onMidAnimation = false;
			skipUpdate = false;
			color.a = 0;
			timer->Start();
		}
		void LoadingCanvas::BeginEndAnimation(){
			app->debug->l("[LoadingCanvas] Begin second part of animation");
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
			if( skipUpdate )
				return;
			const float fadeInTime = 750;
			const float fadeOutTime = 750;
			if( isAnimating ){
				if( onMidAnimation == false ){
					//This means we are animating, but we are in the fade in part
					//Alpha is related to how much time has passed. The animation must be finished in 1 second (fade in)
					color.a = static_cast<Uint8>(Utils::Clamp( std::ceil((timer->GetTicks() / fadeInTime)*255.f), 0.f, 255.f));
					if( timer->GetTicks() >= fadeInTime ){
						timer->Stop();
						onMidAnimation = true;
						midAnimation->Raise(Component::EmptyEventArgs);
					}
				}else{
					if( beginSecondPart ){
						if( color.a == 255 && timer->IsStarted() == false ){
							//With this `if` we make sure that the animation (fade in) ends before we start the fade out animation
							//Doesn't matter if script called `BeginEndAnimation()` earlier than expected
							timer->Start();
						}else{
							//This means we are ready to go fade out and the fade in animation ended
							color.a = static_cast<Uint8>( 255.f - Utils::Clamp( std::ceil((timer->GetTicks() / fadeOutTime)*255.f), 0.f, 255.f) );
							if( timer->GetTicks() >= fadeOutTime ){
								timer->Stop();
								endAnimation->Raise(Component::EmptyEventArgs);
								skipUpdate = true;
							}
						}
					}
					
				}
			}
		}
		void LoadingCanvas::Draw(){
			if( isAnimating ){
				app->sdl->SetRenderColor(color);
				SDL_RenderFillRect(app->sdl->renderer, &carp);
			}
		}

		void LoadingCanvas::Reset(){
			//does nothing but is called when gamesessionmanager changes
		}
	}
}