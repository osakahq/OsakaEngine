 #include "stdafx.h"

#ifndef RPGLIB_FADEINFADEOUTEFFECT_H
#define RPGLIB_FADEINFADEOUTEFFECT_H

#include "Effect.h"

namespace Osaka{
	namespace RPGLib{

		class FadeInFadeOutEffect : public Effect{
		public:
			FadeInFadeOutEffect();
			~FadeInFadeOutEffect();

			void Update() override;
			/* Resets so that it starts fresh. */
			void Reset() override;

			/* Owner. Mid animation is when the animation is in total back */
			Component::EventHandlerPTR midAnimation;
			/* Owner. End animation is when the animation is done and scene is ready to take itself out */
			Component::EventHandlerPTR endAnimation;
		protected:
			/* Used for LoadingScene */
			bool pause_on_midanim;
			TimerPTR timer;
			Uint8 alpha;
		private:
		};
	}
}

#endif