 #include "stdafx.h"

#ifndef RPGLIB_DRAWABLE_H
#define RPGLIB_DRAWABLE_H

#include "engine_include.h"
#include "osaka_forward.h"

#define DRAWABLE_MAXEFFECTS 10
namespace Osaka{
	namespace RPGLib{

		class Drawable{
		public:
			Drawable(SDL_Renderer* raw_renderer);
			/* Drawable will call for every effect: `effect->Deattach()` */
			virtual ~Drawable();
			
			/* This is called from Canvas */
			virtual void Reset();
			virtual void Update();
			void Draw();
			
			/*******************************************************************/
			//Attributes (also for DrawableTexture)
			Engine::RGBA rgba;
			double angle;
			/* This variable holds the coordinates of the center of the image. 
			 * Relative to `quad` */
			SDL_Point center_point;
			SDL_RendererFlip flip;
			SDL_Rect quad; //x,y and h,w
			/* NOT Owner. Raw pointer (raw_pointer) */
			SDL_Renderer* raw_renderer;
			/*******************************************************************/

			void AddMod(Modifier* effect);
			void AddMod(Modifier* effect, DrawableModifierArgs& args);
			/* Normally, the effects should deattach themselves, so this function is "if you need to remove one effect manually" */
			void RemoveMod(Modifier* effect);
			void RemoveMods();

			/* Called from Mod */
			void __Mod_Deattach(Modifier* effect);
			/* Called from Mod (attach=true when attaching ++, false when deattaching --)*/
			void __Mod_Need(bool ex, bool transparency, bool attach);
		protected:
			/* We switch draw functions only when needed. Default: _Draw */
			std::function<void(void)> draw_func; 
			virtual void _Draw();
			/* Expensive draw (RenderCopyEx) */
			virtual void _DrawEx();
			/* Transparency */
			virtual void _DrawTransparency();
			/* `RenderCopyEx` with Transparency. */
			virtual void _DrawTransparencyEx();
			/* We need to count how many effects need what. if both are 0, then we call _Draw
			 * Consulted when attaching/deattaching */
			int need_transparency;
			int need_ex;

			//---------------------------------------------------------------------------------------------//
			/* NOT Owner. */
			std::unordered_map<Modifier*, bool> effects_in_list;
			/* NOT Owner. Has the same items as `effects` */
			std::vector<Modifier*> stack_effects;
			/* NOT Owner. Because vector invalidates the iterator, we need a temp list */
			Modifier* temp_stack[DRAWABLE_MAXEFFECTS];
			int temp_stack_items;

			bool has_list_changed;

			void SetDrawFunc();
		};
	}
}

#endif