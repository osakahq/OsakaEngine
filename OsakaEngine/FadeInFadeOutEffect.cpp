 #include "stdafx.h"

#include "Timer.h"
#include "FadeInFadeOutEffect.h"

namespace Osaka{
	namespace RPGLib{

		FadeInFadeOutEffect::FadeInFadeOutEffect(){
			midAnimation = std::make_shared<Component::EventHandler>();
			endAnimation = std::make_shared<Component::EventHandler>();
		}
		FadeInFadeOutEffect::~FadeInFadeOutEffect(){
			//There are no owners and so, there is no `_delete()`
			//There is no need for nullptr for the EventHandlers
			//No need for timer = nullptr either.
		}

		void FadeInFadeOutEffect::Update(){

		}
		
		void FadeInFadeOutEffect::Reset(){
			//Remember that this is also called from Drawable:AddEffect.
		}
	}
}