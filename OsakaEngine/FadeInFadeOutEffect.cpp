 #include "stdafx.h"

#include "Drawable.h"
#include "Utils.h"
#include "EventHandler.h"
#include "EventArgs.h"
#include "Timer.h"
#include "FadeInFadeOutEffect.h"

namespace Osaka{
	namespace RPGLib{

		FadeInFadeOutEffect::FadeInFadeOutEffect(Timer* timer){
			this->timer = timer;
			_Construct();
		}
		
		void FadeInFadeOutEffect::_Construct(){
			midAnimation = new Component::EventHandler();
			endAnimation = new Component::EventHandler();

			pause_on_midanim = true;
			alpha = 0;
			begin = false;
			beginSecondPart = false;
			onMidAnimation = false;
			beginStillTime = false;

			fadeInTime = 750;
			fadeOutTime = 750;
			stillTime = 750;
		}
		FadeInFadeOutEffect::~FadeInFadeOutEffect(){
			delete midAnimation; midAnimation = NULL;
			delete endAnimation; endAnimation = NULL;
			delete timer; timer = NULL;
		}

		void FadeInFadeOutEffect::__Drawable_Mod(Drawable& obj){
			//We could check beforehand if the obj is inside `objs` map var (base).
			obj.rgba.a = alpha;
		}
		void FadeInFadeOutEffect::_Update(){
			if( begin ){
				//This means we are animating, but we are in the fade in part
				//Alpha is related to how much time has passed. The animation must be finished in 1 second (fade in)
				alpha = static_cast<Uint8>(Utils::Clamp( std::ceil((timer->GetTicks() / fadeInTime)*255.f), 0.f, 255.f));
				if( timer->GetTicks() >= fadeInTime ){
					timer->Start();
					beginStillTime = true;
					begin = false;
				}
			}else if( beginStillTime ){
				if( timer->GetTicks() >= stillTime ){
					LOG("[FadeInFadeOutEffect] Update -> !onMidAnimation [mid]\n");
					timer->Stop();
					onMidAnimation = true;
					beginStillTime = false;
					midAnimation->Raise(Component::EventArgs::CreateEmptyArgs());

					if( pause_on_midanim == false ){
						beginSecondPart = true;
					}
				}
			}else if( onMidAnimation ){ 
				if( beginSecondPart ){ 
					if( alpha == 255 && timer->IsStarted() == false ){
						//With this `if` we make sure that the animation (fade in) ends before we start the fade out animation
						//Doesn't matter if script called `BeginEndAnimation()` earlier than expected
						timer->Start();
					}else{
						//This means we are ready to go fade out and the fade in animation ended
						alpha = static_cast<Uint8>( 255.f - Utils::Clamp( std::ceil((timer->GetTicks() / fadeOutTime)*255.f), 0.f, 255.f) );
						if( timer->GetTicks() >= fadeOutTime ){
							LOG("[FadeInFadeOutEffect] Update -> beginSecondPart [end]\n");
							timer->Stop();
							endAnimation->Raise(Component::EventArgs::CreateEmptyArgs());
							//This is when the effect completes the process.
							this->OneLoop();
						}
					}
				}	
			}
			
		}
		void FadeInFadeOutEffect::BeginEndAnimation(){
			beginSecondPart = true;
		}
		void FadeInFadeOutEffect::Reset(){
			beginSecondPart = false;
			beginStillTime = false;
			onMidAnimation = false;
			begin = true;
			alpha = 0;
			timer->Start();
		}
	}
}