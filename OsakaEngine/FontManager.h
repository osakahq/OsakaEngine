 #include "stdafx.h"
#ifndef RPGLIB_FONTMANAGER_H
#define RPGLIB_FONTMANAGER_H
#include "rpglib_include.h"
#include "osaka_forward.h"

/* It is 128 because in the standard char has 128 representable characters: http://www.cplusplus.com/doc/ascii/ 
 * List of characters: http://web.cs.mun.ca/~michael/c/ascii-table.html */
#define FONTMANAGER_MAX_CHAR 128

namespace Osaka{
	namespace RPGLib{
		
		class FontManager{
		public:
			FontManager(TextureManager* texturem, const std::string& _fontmap_error, int _space_x, int _space_y);
			~FontManager();
			
			void SetFontmap(unorderedmap_fontcharacter_data& fontmap);
			void Init(SDL_Renderer* _renderer);
			
			void RenderTextLine(const char* text, const int x, const int y);
			void RenderTextLine(const std::string& text, const int x, const int y);

			void RenderTextMultiple(const char* text, const int x, const int y, const int max_slots);
			void RenderTextMultiple(const std::string& str, const int x, const int y, const int max_slots);

			/* Gives away ownership. */
			StaticText* CreateStaticText(const char* text, const int x, const int y, const int max_slots);
		/* ----------------------------------------------------------------------------------- */
		private:
			const std::string fontmap_error;
			const int fontmap_char_space_x;
			const int fontmap_char_space_y;
			/* NOT Owner. */
			const unorderedmap_fontcharacter_data* fontmap;
			/* NOT Owner */
			TextureManager* texturem;

			/* Owner of all sprite_into*. This is the cache to draw faster. The index number is actually the letter (char to int) */
			sprite_info* sprites[FONTMANAGER_MAX_CHAR];

			/* NOT Owner */
			SDL_Renderer* raw_renderer;
		};
	}
}
#endif