 #include "stdafx.h"
#ifndef RPGLIB_FONTMANAGER_H
#define RPGLIB_FONTMANAGER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class FontManager{
		public:
			FontManager(TextureManagerPTR& texture, std::string _fontmap_error);
			~FontManager();
			void _delete();
			void SetFontmap(unorderedmap_fontcharacter_dataPTR& fontmap);

			void RenderText(const char* text, const Engine::render_info& render);
			void RenderText(const std::string text, const Engine::render_info& render);
		/* ----------------------------------------------------------------------------------- */
		private:
			const std::string fontmap_error;
			/* NOT Owner. */
			unorderedmap_fontcharacter_dataPTR fontmap;
			/* NOT Owner */
			TextureManagerPTR texture;
		};
	}
}
#endif