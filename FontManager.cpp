#include "stdafx.h"
#include "rpglib_include.h"
#include "gamedata_include.h"
#include "TextureManager.h"
#include "FontManager.h"

namespace Osaka{
	namespace RPGLib{
		FontManager::FontManager(TextureManagerPTR& texture, std::string _fontmap_error, int _space_x, int _space_y) 
			: fontmap_error(_fontmap_error), fontmap_char_space_x(_space_x), fontmap_char_space_y(_space_y)
		{
			fontmap = nullptr;
			this->texture = texture;

			for(int i = 0; i < FONTMANAGER_MAX_CHAR; ++i)
				sprites[i] = NULL;
		}
		FontManager::~FontManager(){

		}
		void FontManager::_delete(){
			raw_renderer = NULL;

			for(int i = 0; i < FONTMANAGER_MAX_CHAR; ++i){
				if( sprites[i] != NULL )
					delete sprites[i];
			}
			
			fontmap = nullptr;
			texture = nullptr;
		}
		void FontManager::SetFontmap(unorderedmap_fontcharacter_dataPTR& fontmap){
			this->fontmap = fontmap;
		}
		void FontManager::Init(SDL_Renderer& _renderer){
			raw_renderer = &_renderer;

			for( auto it = fontmap->begin(); it != fontmap->end(); ++it ){
				//it->first = char
				if( (int)it->first >= FONTMANAGER_MAX_CHAR )
					throw std::exception("[FontManager] Outside of limit > FONTMANAGER_MAX_CHAR");
				sprites[(int)it->first] = texture->CreateSpriteRAWPointer(it->second->sprite.c_str());
			}
		}

		void FontManager::RenderTextLine(const char* text, const int x, const int y){
			//Because we know all fontmap sprites are the same size, we set the quad space_x, space_y
			SDL_Rect quad = {x, y, fontmap_char_space_x, fontmap_char_space_y};
			for(const char* c = text; *c; ++c){
				SDL_RenderCopy(raw_renderer, sprites[(int)*c]->raw_texture, &sprites[(int)*c]->clip, &quad);
				quad.x += fontmap_char_space_x;
			}
		}
		void FontManager::RenderTextLine(const std::string text, const int x, const int y){
			//Because we know all fontmap sprites are the same size, we set the quad space_x, space_y
			SDL_Rect quad = {x, y, fontmap_char_space_x, fontmap_char_space_y};
			for(const char c : text){
				SDL_RenderCopy(raw_renderer, sprites[(int)c]->raw_texture, &sprites[(int)c]->clip, &quad);
				quad.x += fontmap_char_space_x;
			}
		}

		void FontManager::RenderTextMultiple(const char* text, const int x, const int y, const int max_slots){
			return;
			Engine::render_info_ex render(x, y, 0, NULL, SDL_FLIP_NONE);

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
					render.y += fontmap_char_space_y;
					slot = 1;
				}
				if( *c != ' ' ){
					//texture->RenderSprite(fontmap->at(*c)->sprite, render);
				}
				render.x += fontmap_char_space_x;
			}
		}
	}
}