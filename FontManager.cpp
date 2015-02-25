#include "stdafx.h"
#include "gamedata_include.h"
#include "TextureManager.h"
#include "FontManager.h"

namespace Osaka{
	namespace RPGLib{
		FontManager::FontManager(TextureManagerPTR& texture, std::string _fontmap_error, int _space_x, int _space_y) 
			: fontmap_error(_fontmap_error), space_x(_space_x), space_y(_space_y)
		{
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

		void FontManager::RenderTextLine(const char* text, const int x, const int y){
			Engine::render_info render(x, y, 0, NULL, SDL_FLIP_NONE);

			for(const char* c = text; *c; ++c){
				texture->RenderSprite(fontmap->at(*c)->sprite, render);
				render.x += space_x;
			}
		}
		void FontManager::RenderTextLine(const std::string text, const int x, const int y){
			Engine::render_info render(x, y, 0, NULL, SDL_FLIP_NONE);

			for(const char c : text){
				texture->RenderSprite(fontmap->at(c)->sprite, render);
				render.x += space_x;
			}
		}

		void FontManager::RenderTextMultiple(const char* text, const int x, const int y, const int max_slots){
			Engine::render_info render(x, y, 0, NULL, SDL_FLIP_NONE);

			int slot = 0;
			for(const char* c = text; *c; ++c){
				if( slot++ == max_slots ){
					/* I think Ascension is responsible of crafting the message according to its message box size
					 * But just in case, we do a simple check, if current c is A-Za-z and next also is A-Za-z */
					//texture->RenderSprite(fontmap->at(' ')->sprite, render);

					//A-Z
					//if( *c >= 65 && *c <= 90 && *c >= 97 && *c <= 122 ){
					//	if( *(c+1) ){
					//
					//	}
					//}

					render.x = x;
					render.y += space_y;
					slot = 1;
				}
				if( *c != ' ' ){
					texture->RenderSprite(fontmap->at(*c)->sprite, render);
				}
				render.x += space_x;
			}
		}
	}
}