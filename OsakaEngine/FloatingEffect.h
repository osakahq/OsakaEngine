 #include "stdafx.h"

#ifndef RPGLIB_FLOATINGEFFECT_H
#define RPGLIB_FLOATINGEFFECT_H

#include "Modifier.h"
#include "DrawableModifierArgs.h"

namespace Osaka{
	namespace RPGLib{

		/* With this we can set a different distance to travel for each drawable obj (separate) */
		struct DrawableModFloatingArgs : DrawableModifierArgs{
			DrawableModFloatingArgs(const int wY, const float _percentage_delta)
				: wiggleY(wY), 
				percentage_delta(_percentage_delta)
			{
			}
			/* How much are we moving */
			const int wiggleY;
			/* percentage_easing_delta should be between >0.01 to 1
			 * This is the percentage of delta, the lower percentage_easing_delta, the lower easing_delta will be
			 * . making the animation go slower */
			const float percentage_delta;
		};

		struct floating_info{
			floating_info()
				: wiggleY(0), percentage_delta(0), middle_pixels_y(0)
			{}
			floating_info(const int wY, const float _percentage_delta) : 
				/* The reason we need to add +1 is because example:
				 * wiggleY is 20, from 19 to 20 it takes too much time, so when it reaches 20, 
				 * it will almost instantly move again and the animation looks shacky(weird)
				 * !ALSO!, because of how it works, it will never reach 21 and between 20 and reaching to 20.999, 
				 * it gives a nice delay so that it doesn't change instantly */
				wiggleY(wY+1),
				percentage_delta(_percentage_delta),
				middle_pixels_y(static_cast<int>(static_cast<float>(wiggleY-1) / 2.f))
			{
				/* In terms of floating perspective we are starting at the middle,
				 * So we are already in the middle. */
				traveled_y = static_cast<float>(wiggleY-1) / 2.f;
				/* traveled_y = 5.656. pixels_to_travel_y = [5].656. we are the pixel 5
				 * `middle_pixels_y` and `traveled_y` have the same ammount but one is int and the other is float */
				pixels_traveled_y = middle_pixels_y;

				up = true;
				phase = 0;
			}

			/* Called in FloatingEffect::Reset() */
			void Reset(){
				//Reset drawable vars
				up = true;
				//Remember that we start at the middle.
				traveled_y = static_cast<float>(wiggleY-1) / 2.f;
				pixels_traveled_y = middle_pixels_y;
				phase = 0;
			}

			/* We add 0.X (floating numbers) to traveled_y but because there are only pixels
			 * We need pixels_to_travel_y for the whole number. */
			float traveled_y;
			/* We need this so we can actually move by pixels. See _Update */
			int pixels_traveled_y;
			//Is the animation going up or down?
			bool up;

			/* We need phase so we can know when we have done 1 loop */
			int phase; //0 = starting, 1 = reached up, 2 = reached down
			
			/* These 2 vars are gotten from `DrawableModFloatingArgs` */
			const int wiggleY;
			const float percentage_delta;
			/* This is the starting point = wiggleY / 2 */
			const int middle_pixels_y; //!IMPORTANT: This variable must be AFTER `wiggleY`
		};

		class FloatingEffect : public Modifier{
		public:
			FloatingEffect(TimeManager* timerm);
			virtual ~FloatingEffect();

			void __Drawable_Mod(Drawable& obj) override;
			bool __Drawable_Attach(Drawable* obj, DrawableModifierArgs& args) override;
			void __Drawable_Deattach(Drawable* obj) override;
		protected:
			void Reset() override;
			void _Update() override;

			/* This is delta divided by 100 = 0.16 */
			float delta;

			/* NOT Owner */
			TimeManager* timerm;
			/* NOT Owner */
			std::unordered_map<Drawable*, floating_info> floatings;
		};
	}
}

#endif