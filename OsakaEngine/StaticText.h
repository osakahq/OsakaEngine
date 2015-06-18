 #include "stdafx.h"
#ifndef RPGLIB_STATICTEXT_H
#define RPGLIB_STATICTEXT_H
#include "rpglib_include.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		
		class StaticText{
		public:
			StaticText(SDL_Renderer* _renderer, std::vector<sprite_info*>& sprites, int max_slots, int space_x, int space_y);
			~StaticText();
			
			/* sprite_info has a x and y (quad) when created, they have the initial coordinates */
			void Render();
			/* If you want to render in a different position, t */
			void Change(const int x, const int y);
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner */
			SDL_Renderer* raw_renderer;

			/* Owner of all sprite_info*. This is an array of sprite_info* */
			std::vector<sprite_info*> sprites;

			/* This is the maximum slots on x axis. */
			int max_slots;

			/* These are the size of each char in the fontmap */
			const int fontmap_char_space_x;
			const int fontmap_char_space_y;
		};
	}
}
#endif