 #include "stdafx.h"
#include "Layer.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Debug.h"
#include "Timer.h"
#include "EventArgs.h"
#include "EventHandler.h"

#include "RPGApplication.h"
#include "Utils.h"
#include "LoadingFadeCanvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		LoadingFadeCanvas::LoadingFadeCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler, TimerPTR& timer) : Canvas(raw_renderer, ruler){
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

			carp.x = ruler->x_top_left_corner;
			carp.y = ruler->y_top_left_corner;
			carp.w = ruler->max_width;
			carp.h = ruler->max_height;

			this->timer = timer;
		}
		LoadingFadeCanvas::~LoadingFadeCanvas(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingCanvas");
#endif
			//These should go here because it doesn't matter if LoadingFadeScript has the reference for Canvas.
			//If _delete is called before LoadingFadeScript::_delete then it will try to unhook the event but since no one has the references
			//the EventHandlerPTR will go away
			midAnimation = nullptr;
			endAnimation = nullptr;
		}
		void LoadingFadeCanvas::_delete(){
			Canvas::_delete();
			
			timer->_delete(); timer = nullptr;
		}
		
		void LoadingFadeCanvas::StartAnimation(TransitionType::Value type){
			this->type = type;
			isAnimating = true;
			beginSecondPart = false;
			onMidAnimation = false;
			skipUpdate = false;
			color.a = 0;
			timer->Start();
		}
		void LoadingFadeCanvas::BeginEndAnimation(){
			layer_parent->app->debug->l("[LoadingCanvas] Begin second part of animation");
			beginSecondPart = true;
		}
		
		void LoadingFadeCanvas::Update(){
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
		void LoadingFadeCanvas::Draw(){
			if( isAnimating ){
				//app->sdl->SetRenderColor(color);
				SDL_SetRenderDrawColor(raw_renderer, color.r, color.g, color.b, color.a);
				SDL_SetRenderDrawBlendMode(raw_renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderFillRect(raw_renderer, &carp);
				SDL_SetRenderDrawBlendMode(raw_renderer, SDL_BLENDMODE_NONE);
			}
		}

	}
}