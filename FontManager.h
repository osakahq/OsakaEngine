 #include "stdafx.h"
#ifndef RPGLIB_FONTMANAGER_H
#define RPGLIB_FONTMANAGER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class FontManager{
		public:
			FontManager(TextureManagerPTR& texture, std::string _fontmap_error, int _space_x, int _space_y);
			~FontManager();
			void _delete();
			void SetFontmap(unorderedmap_fontcharacter_dataPTR& fontmap);

			void RenderTextLine(const char* text, const int x, const int y);
			void RenderTextLine(const std::string text, const int x, const int y);

			void RenderTextMultiple(const char* text, const int x, const int y, const int max_slots);
		/* ----------------------------------------------------------------------------------- */
		private:
			const std::string fontmap_error;
			const int space_x;
			const int space_y;
			/* NOT Owner. */
			unorderedmap_fontcharacter_dataPTR fontmap;
			/* NOT Owner */
			TextureManagerPTR texture;
		};
	}
}
#endif