 #include "stdafx.h"

#ifndef RPGLIB_FADEINFADEOUTEFFECT_H
#define RPGLIB_FADEINFADEOUTEFFECT_H

#include "Effect.h"

namespace Osaka{
	namespace RPGLib{

		class FadeInFadeOutEffect : public Effect{
		public:
			FadeInFadeOutEffect(TimerPTR& timer);
			~FadeInFadeOutEffect();

			void Update() override;
			void Reset() override;

			/* Owner. Mid animation is when the animation is in total back */
			Component::EventHandlerPTR midAnimation;
			/* Owner. End animation is when the animation is done and scene is ready to take itself out */
			Component::EventHandlerPTR endAnimation;

			void BeginEndAnimation();

			float fadeInTime;
			float fadeOutTime;
		protected:
			/* In case you don't need to wait for something. */
			bool pause_on_midanim;
			TimerPTR timer;
			Uint8 alpha;

			/* TODO: update description: When the animation starts, it has to stop in black (and letters "loading"), we need script to let us know when to being the end animation */
			bool beginSecondPart;
			/* So we can know we finished, the first animation */
			bool onMidAnimation;

		private:
		};
	}
}

#endif