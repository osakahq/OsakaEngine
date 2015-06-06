 #include "stdafx.h"

#ifndef RPGLIB_EFFECT_H
#define RPGLIB_EFFECT_H

#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class Effect{
		public:
			Effect();
			virtual ~Effect();

			/* Called from Drawable:AddEffect */
			virtual void Attach(DrawablePTR& obj);
			virtual void Update();
			//Effect doesn't have Draw because it shouldn't draw anything.

			/* In case you want to have a duplicated effect in a drawable object */
			void ChangeId(std::string id);
			std::string id;	

			/* Called from: Drawable(AddEffect, When the object is resetted, etc.) Resets so that it starts fresh. */
			virtual void Reset();

			void OneLoopDone();
		protected:
			bool repeat;
			/* Param. How many times effect is gonna repeat the whole process */
			int times_repeat;
			/* Var. Current loop, if its equal than `times_repeat` then stop or deattach. */
			int current_loop;
			/* Param. When its finished, should it deattach itself? */
			bool deattach;

			/* Derived class must consult the value. */
			bool isActive;

			DrawablePTR obj;
		private:
		};
	}
}

#endif