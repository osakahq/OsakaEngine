 #include "stdafx.h"

#ifndef RPGLIB_MODIFIER_H
#define RPGLIB_MODIFIER_H

#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class Modifier{
		public:
			Modifier();
			virtual ~Modifier();

			virtual void Set(int times_repeat, bool deattach, bool forever_repeat);
			/* Called from owner (Ex: Canvas) */
			void Update();
			/* Sets current_loop to 0 and calls `Reset()`. Should only be called by the owner. */
			void Restart();

			/* Called from Drawable */
			virtual void __Drawable_Mod(Drawable& raw_obj) = 0;
			/* Called from Drawable:AddEffect
			 * If you override this in baseclass, then you should consult the return value */
			virtual bool __Drawable_Attach(Drawable* obj);
			/* Called when the effect is removed from the object (Called from Drawable: remove functions) */
			virtual void __Drawable_Deattach(Drawable* obj);
		protected:
			/* This is the one base class should override */
			virtual void _Update() = 0;
			/* Should only be called by the class itself */
			virtual void Reset() = 0;
			/* Called from derived class when 1 loop ended */
			void OneLoop();

			bool forever_repeat;
			/* Param. How many times effect is gonna repeat the whole process */
			int times_repeat;
			/* Var. Current loop, if its equal than `times_repeat` then stop or deattach. */
			int current_loop;
			/* Param. When its finished, should it deattach itself? */
			bool deattach;

			/* Not owner. */
			std::unordered_map<Drawable*, Drawable*> objs;
		private:
		};
	}
}

#endif