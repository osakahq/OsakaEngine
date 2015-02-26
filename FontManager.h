 #include "stdafx.h"
#ifndef RPGLIB_FONTMANAGER_H
#define RPGLIB_FONTMANAGER_H
#include "rpglib_include.h"
#include "osaka_forward.h"

/* It is 128 because in the standard char has 128 representable characters: http://www.cplusplus.com/doc/ascii/ */
#define FONTMANAGER_MAX_CHAR 128

namespace Osaka{
	namespace RPGLib{
		
		class FontManager{
		public:
			FontManager(SDL_Renderer& renderer, TextureManagerPTR& texture, std::string _fontmap_error, int _space_x, int _space_y);
			~FontManager();
			void _delete();
			void Init();
			void SetFontmap(unorderedmap_fontcharacter_dataPTR& fontmap);

			void RenderTextLine(const char* text, const int x, const int y);
			void RenderTextLine(const std::string text, const int x, const int y);

			void RenderTextMultiple(const char* text, const int x, const int y, const int max_slots);
		/* ----------------------------------------------------------------------------------- */
		private:
			const std::string fontmap_error;
			const int fontmap_char_space_x;
			const int fontmap_char_space_y;
			/* NOT Owner. */
			unorderedmap_fontcharacter_dataPTR fontmap;
			/* NOT Owner */
			TextureManagerPTR texture;

			/* Owner of all sprite_into*. This is the cache to draw faster. The index number is actually the letter (char to int) */
			sprite_info* sprites[FONTMANAGER_MAX_CHAR];

			/* NOT Owner */
			SDL_Renderer* raw_renderer;
		};
	}
}
#endif