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
			virtual void Update();
			virtual void Reset();
			/* Inexpensive draw */
			virtual void Draw();
			/* Expensive draw (RenderCopyEx) */
			virtual void DrawEx();
			/* Draw with blend. Don't call this while using a DrawableTexture.
			 * For that you need to call a function with the texture (See `Texture`) */
			virtual void DrawBlend();

			/* Drawable will call `effect->Attach(this)` */
			void AddMod(Modifier* effect);
			/* Normally, the effects should deattach themselves, so this function is "if you need to remove one effect manually" */
			void RemoveMod(Modifier* effect);
			void RemoveMods();

			/* Called from Mod */
			void __Mod_Deattach(Modifier* effect);
		protected:
			/* NOT Owner. */
			std::unordered_map<Modifier*, bool> effects_in_list;
			/* NOT Owner. Has the same items as `effects` */
			std::vector<Modifier*> stack_effects;
			/* NOT Owner. Because vector invalidates the iterator, we need a temp list */
			Modifier* temp_stack[DRAWABLE_MAXEFFECTS];
			int temp_stack_items;

			bool has_list_changed;

			/* NOT Owner. Raw pointer (raw_pointer) */
			SDL_Renderer* raw_renderer;
		private:
		};
	}
}

#endif