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

			void __Drawable_Mod(Drawable& obj) override;
			void Set(float fadeInTime);
		protected:
			void Reset() override;
			void _Update() override;

			float fadeInTime;
			Uint8 alpha;

			/* Owner */
			Timer* timer;
		};
	}
}

#endif