 #include "stdafx.h"

#ifndef RPGLIB_FLOATINGEFFECT_H
#define RPGLIB_FLOATINGEFFECT_H

#include "Modifier.h"
#include "DrawableModifierArgs.h"

namespace Osaka{
	namespace RPGLib{

		/* With this we can set a different distance to travel for each drawable obj (separate) */
		struct DrawableModFloatingArgs : DrawableModifierArgs{
			DrawableModFloatingArgs(const int wY):wiggleY(wY){}
			const int wiggleY;
			//const int easing_delta;
		};

		struct floating_info{
			floating_info(): wiggleY(0){}
			floating_info(const int wY)
				: wiggleY(wY+1) //explain why TTTTTTTTTTOOOOOOOOddddOOOOOOOOOOOO
			{
				//In terms of floating perspective we are starting at the middle,
				//So we are already in the middle.
				traveled_y = static_cast<float>(wiggleY) / 2.0f;
				up = true;
				
				pixels_to_travel_y = static_cast<int>(traveled_y);
			}
			float traveled_y;
			//We need this so we can actually move by pixels.
			int pixels_to_travel_y;
			bool up;
			const int wiggleY;
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

			float easing_delta;

			/* NOT Owner */
			TimeManager* timerm;
			/* NOT Owner */
			std::unordered_map<Drawable*, floating_info> floatings;
		};
	}
}

#endif