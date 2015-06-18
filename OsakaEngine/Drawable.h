 #include "stdafx.h"

#ifndef RPGLIB_DRAWABLE_H
#define RPGLIB_DRAWABLE_H

#include "engine_include.h"
#include "rpglib_include.h"
#include "osaka_forward.h"

#define DRAWABLE_MAXEFFECTS 40
namespace Osaka{
	namespace RPGLib{

		class Drawable{
		public:
			Drawable(SDL_Renderer* raw_renderer);
			/* Drawable will call for every effect: `effect->Deattach()` */
			virtual ~Drawable();
			
			Engine::RGBA_HEX rgba;
			double angle;
			SDL_Point point;
			SDL_RendererFlip flip;
			
			/* This is called from Canvas */
			virtual void Reset();
			virtual void Update();
			virtual void Draw();

			void ResetAllEffects();
			/* Drawable will call `effect->Attach(this)` */
			void AddEffect(Effect* effect);
			/* Normally, the effects should deattach themselves, so this function is "if you need to remove one effect manually" */
			void RemoveEffect(const std::string& id);
			void RemoveAllEffects();
		protected:
			/* NOT Owner. */
			std::unordered_map<std::string, Effect*> effects;
			/* NOT Owner. Has the same items as `effects` */
			std::vector<Effect*> stack_effects;
			/* NOT Owner. Because vector invalidates the iterator, we need a temp list */
			Effect* temp_stack[DRAWABLE_MAXEFFECTS];
			int temp_stack_items;

			bool has_list_changed;

			/* NOT Owner. Raw pointer (raw_pointer) */
			SDL_Renderer* raw_renderer;
		private:
		};
	}
}

#endif