 #include "stdafx.h"

#include "Drawable.h"
#include "DrawableTexture.h"
#include "Utils.h"
#include "EventHandler.h"
#include "EventArgs.h"
#include "Timer.h"
#include "Utils.h"
#include "FadeInEffect.h"

namespace Osaka{
	namespace RPGLib{

		FadeInEffect::FadeInEffect(Timer* timer) : Modifier(false, true){
			this->timer = timer;
			fadeInTime = 4000;
			alpha = 0;
		}
		
		FadeInEffect::~FadeInEffect(){
			delete timer; timer = NULL;
		}
		void FadeInEffect::Set(float fadeInTime){
			this->fadeInTime = fadeInTime;
		}
		void FadeInEffect::__Drawable_Mod(Drawable& obj){
			obj.rgba.a = alpha;
		}
		void FadeInEffect::_Update(){
			alpha = static_cast<Uint8>(Utils::Clamp( std::ceil((timer->GetTicks() / fadeInTime)*255.f), 0.f, 255.f));
			if( alpha == 255 ){
				//The next `Modifier::Update`, Reset will be called.
				timer->Stop();
				/* Since this effect only works 1 way. It will be automatically deattached.
				 * forever_repeat is false by default  */
				OneLoop();
			}
		}
		
		void FadeInEffect::Reset(bool loop_finished){
			timer->Start();
			alpha = 0;
		}
	}
}