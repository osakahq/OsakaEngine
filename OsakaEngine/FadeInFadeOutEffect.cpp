 #include "stdafx.h"

#include "Drawable.h"
#include "Utils.h"
#include "EventHandler.h"
#include "EventArgs.h"
#include "Timer.h"
#include "FadeInFadeOutEffect.h"

namespace Osaka{
	namespace RPGLib{

		FadeInFadeOutEffect::FadeInFadeOutEffect(Timer* timer) : Effect("_fadeinfadeout"){
			this->timer = timer;
			_Construct();
		}
		FadeInFadeOutEffect::FadeInFadeOutEffect(const std::string& id, Timer* timer) : Effect(id){
			this->timer = timer;
			_Construct();
		}
		void FadeInFadeOutEffect::_Construct(){
			midAnimation = new Component::EventHandler();
			endAnimation = new Component::EventHandler();

			pause_on_midanim = true;
			alpha = 0;
			beginSecondPart = false;
			onMidAnimation = false;

			fadeInTime = 750;
			fadeOutTime = 750;
		}
		FadeInFadeOutEffect::~FadeInFadeOutEffect(){
			delete midAnimation; midAnimation = NULL;
			delete endAnimation; endAnimation = NULL;
			delete timer; timer = NULL;
		}

		void FadeInFadeOutEffect::Update(){
			if( !isActive )
				return;
			
			if( onMidAnimation == false ){
				//This means we are animating, but we are in the fade in part
				//Alpha is related to how much time has passed. The animation must be finished in 1 second (fade in)
				alpha = static_cast<Uint8>(Utils::Clamp( std::ceil((timer->GetTicks() / fadeInTime)*255.f), 0.f, 255.f));
				raw_obj->rgba.a = alpha;
				if( timer->GetTicks() >= fadeInTime ){
					printf("[FadeInFadeOutEffect] Update -> !onMidAnimation [mid]\n");
					timer->Stop();
					onMidAnimation = true;
					midAnimation->Raise(Component::EmptyEventArgs);

					if( pause_on_midanim == false ){
						beginSecondPart = true;
					}
				}
			}else{
				if( beginSecondPart ){
					if( alpha == 255 && timer->IsStarted() == false ){
						//With this `if` we make sure that the animation (fade in) ends before we start the fade out animation
						//Doesn't matter if script called `BeginEndAnimation()` earlier than expected
						timer->Start();
					}else{
						//This means we are ready to go fade out and the fade in animation ended
						alpha = static_cast<Uint8>( 255.f - Utils::Clamp( std::ceil((timer->GetTicks() / fadeOutTime)*255.f), 0.f, 255.f) );
						raw_obj->rgba.a = alpha;
						if( timer->GetTicks() >= fadeOutTime ){
							printf("[FadeInFadeOutEffect] Update -> beginSecondPart [end]\n");
							timer->Stop();
							endAnimation->Raise(Component::EmptyEventArgs);
							//This is when the effect completes the process.
							this->OneLoopDone();
						}
					}
				}
					
			}
			
		}
		void FadeInFadeOutEffect::BeginEndAnimation(){
			beginSecondPart = true;
		}
		void FadeInFadeOutEffect::Reset(){
			Effect::Reset();
			beginSecondPart = false;
			onMidAnimation = false;
			alpha = 0;
			raw_obj->rgba.a = 0;
			timer->Start();
			//Remember that this is also called from Drawable:AddEffect.
		}
	}
}