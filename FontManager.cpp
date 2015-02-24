#include "stdafx.h"
#include "gamedata_include.h"
#include "TextureManager.h"
#include "FontManager.h"

namespace Osaka{
	namespace RPGLib{
		FontManager::FontManager(TextureManagerPTR& texture, std::string _fontmap_error) : fontmap_error(_fontmap_error){
			fontmap = nullptr;
			this->texture = texture;
		}
		FontManager::~FontManager(){

		}
		void FontManager::_delete(){
			fontmap = nullptr;
			texture = nullptr;
		}
		void FontManager::SetFontmap(unorderedmap_fontcharacter_dataPTR& fontmap){
			this->fontmap = fontmap;
		}

		void FontManager::RenderTextLine(const char* text, int x, int y){
			Engine::render_info render(x, y, 0, NULL, SDL_FLIP_NONE);

			for(const char* c = text; *c; ++c){
				texture->RenderSprite(fontmap->at(*c)->sprite, render);
				render.x += 12;
			}
		}
		void FontManager::RenderTextLine(const std::string text, int x, int y){
			Engine::render_info render(x, y, 0, NULL, SDL_FLIP_NONE);

			for(const char c : text){
				texture->RenderSprite(fontmap->at(c)->sprite, render);
				render.x += 12;
			}
		}
	}
}