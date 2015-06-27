 #include "stdafx.h"

#ifndef RPGLIB_FADEINFADEOUTEFFECT_H
#define RPGLIB_FADEINFADEOUTEFFECT_H

#include "Modifier.h"

namespace Osaka{
	namespace RPGLib{

		class FadeInFadeOutEffect : public Modifier{
		public:
			FadeInFadeOutEffect(Timer* timer);
			virtual ~FadeInFadeOutEffect();

			/* Owner. Mid animation is when the animation is in total back */
			Component::EventHandler* midAnimation;
			/* Owner. End animation is when the animation is done and scene is ready to take itself out */
			Component::EventHandler* endAnimation;

			void BeginEndAnimation();

			float fadeInTime;
			float fadeOutTime;
			float stillTime;

			void __Drawable_Mod(Drawable& obj) override;
		protected:
			void Reset(bool loop_finished) override;
			void _Update() override;

			/* In case you don't need to wait for something. */
			bool pause_on_midanim;
			/* Owner */
			Timer* timer;
			Uint8 alpha;

			bool begin;
			bool beginStillTime;
			/* TODO: update description: When the animation starts, it has to stop in black (and letters "loading"), we need script to let us know when to being the end animation */
			bool beginSecondPart;
			/* So we can know we finished, the first animation */
			bool onMidAnimation;

		private:
			void _Construct();
		};
	}
}

#endif