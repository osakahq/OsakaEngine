 #include "stdafx.h"

#ifndef RPGLIB_DRAWABLE_H
#define RPGLIB_DRAWABLE_H

#include "engine_include.h"
#include "rpglib_include.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class Drawable{
		public:
			Drawable(SDL_Renderer* raw_renderer);
			virtual ~Drawable();
			
			Engine::RGBA_HEX rgba;
			double angle;
			SDL_Point point;
			SDL_RendererFlip flip;
			
			/* This is called from Canvas */
			virtual void Reset();
			virtual void Update();
			virtual void Draw();

			void ResetEffect(std::string id);
			void ResetAllEffects();
			void AddEffect(EffectPTR& effect);
			/* Normally, the effects should deattach themselves, so this function is "if you need to remove one effect manually" */
			void RemoveEffect(std::string id);
			void RemoveAllEffects();
		protected:
			/* NOT Owner. There are no owners for EffectPTR (hence no `_delete`) */
			std::vector<EffectPTR> effects;
			/* NOT Owner. Because vector invalidates the iterator, we need a temp list */
			std::vector<EffectPTR> temp_list;
			bool has_list_changed;

			/* NOT Owner. Raw pointer (raw_pointer) */
			SDL_Renderer* raw_renderer;
		private:
		};
	}
}

#endif