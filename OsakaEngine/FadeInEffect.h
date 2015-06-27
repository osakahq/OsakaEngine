 #include "stdafx.h"

#ifndef RPGLIB_FADEINEFFECT_H
#define RPGLIB_FADEINEFFECT_H

#include "Modifier.h"

namespace Osaka{
	namespace RPGLib{

		class FadeInEffect : public Modifier{
		public:
			FadeInEffect(Timer* timer);
			virtual ~FadeInEffect();

			void Set(float fadeInTime);

			void __Drawable_Mod(Drawable& obj) override;
		protected:
			void Reset(bool loop_finished) override;
			void _Update() override;

			float fadeInTime;
			Uint8 alpha;

			/* Owner */
			Timer* timer;
		};
	}
}

#endif