 #include "stdafx.h"

#ifndef RPGLIB_MODIFIER_H
#define RPGLIB_MODIFIER_H

#include "EventArgs.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class ModifierEventArgs : public Component::EventArgs{
		public:
			ModifierEventArgs(bool _mod_deattach) : mod_deattach(_mod_deattach){
			}
			ModifierEventArgs() : mod_deattach(false){
			}
			/* This is to tell that Mod is gonna deattach itself */
			const bool mod_deattach;
		};

		class Modifier{
		public:
			Modifier(bool ne, bool nt);
			virtual ~Modifier();

			void SetRepetitions(int times_repeat, bool forever_repeat);
			/* Called from owner (Ex: Canvas) */
			void Update();
			/* Sets current_loop to 0 and calls `Reset()`. Should only be called by the owner. */
			void Restart();

			/* Owner. Raised everytime 1 loop is done. */
			Component::EventHandler* oneLoop;

			/* Called from Drawable */
			virtual void __Drawable_Mod(Drawable& raw_obj) = 0;
			/* Called from Drawable:AddEffect
			 * If you override this in baseclass, then you should consult the return value
			 * `args` can be ignored if you don't use it and it is deleted when the function call chain ends.
			 * You can use `args` to have unique settings for the drawable objects. See FloatingEffect for an example */
			virtual bool __Drawable_Attach(Drawable* obj, DrawableModifierArgs& args);
			/* Called when the effect is removed from the object (Called from Drawable: remove functions) */
			virtual void __Drawable_Deattach(Drawable* obj);

		protected:
			/* These should be set by the derived class */
			const bool need_ex;
			const bool need_transparency;

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
			/* We need this helper var so that when a loop is done, we can call reset in the `Update` function.
			 * Why? Because if we call reset when `OneLoop` is called, the variables will be resetted and when __Drawable_Mod is called won't have the corresponding values */
			bool loop_was_done;

			/* If its not forever_loop = true and times_repeat was reached, then active = false. */
			bool active;

			/* Not owner. */
			std::unordered_map<Drawable*, Drawable*> objs;
		private:
		};
	}
}

#endif