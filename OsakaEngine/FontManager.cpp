#include "stdafx.h"
#include "rpglib_include.h"
#include "gamedata_include.h"
#include "TextureManager.h"
#include "StaticText.h"
#include "FontManager.h"

namespace Osaka{
	namespace RPGLib{
		FontManager::FontManager(TextureManager* texturem, const std::string& _fontmap_error, int _space_x, int _space_y) 
			: fontmap_error(_fontmap_error), fontmap_char_space_x(_space_x), fontmap_char_space_y(_space_y)
		{
			this->texturem = texturem;

			for(int i = 0; i < FONTMANAGER_MAX_CHAR; ++i)
				sprites[i] = NULL;
		}
		FontManager::~FontManager(){
			raw_renderer = NULL;

			for(int i = 0; i < FONTMANAGER_MAX_CHAR; ++i){
				if( sprites[i] != NULL )
					delete sprites[i];
			}
			
			//fontmap.clear();
			fontmap = NULL;
			texturem = NULL;
		}
		
		void FontManager::SetFontmap(unorderedmap_fontcharacter_data& fontmap){
			this->fontmap = &fontmap;
		}
		void FontManager::Init(SDL_Renderer* _renderer){
			raw_renderer = _renderer;

			for( auto it = fontmap->begin(); it != fontmap->end(); ++it ){
				//it->first = char
				if( (int)it->first >= FONTMANAGER_MAX_CHAR )
					throw std::exception("[FontManager] Outside of limit > FONTMANAGER_MAX_CHAR");
				sprites[(int)it->first] = texturem->CreateSpriteRAWPointer(it->second->sprite);
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

		void FontManager::RenderTextMultiple(const std::string& str, const int x, const int y, const int max_slots){
			RenderTextMultiple(str.c_str(), x, y, max_slots);
		}
		void FontManager::RenderTextMultiple(const char* text, const int x, const int y, const int max_slots){
#ifdef _DEBUG
			if( max_slots <= 1 ){
				throw std::exception("[FontManager] RenderTextMultiple > max_slots is too little");
			}
#endif
			/* This code is also in CreateStaticText. */
			SDL_Rect quad = {x, y, fontmap_char_space_x, fontmap_char_space_y};
			int slot = 0;
			for(const char* c = text; *c; ++c){
				slot++;

				if( slot == max_slots ){
					if( *(c-1) == ' ' ){ //[Hey _] 2 spaces
						//If its time to go to new line, and the behind current one is a space:
						--c; //We need to go back because we didn't print the current one
						quad.x = x;
						quad.y += fontmap_char_space_y;
						slot = 0;
						continue;
					}
					if( *c == ' ' ){
						//If the current one is a space, then we just go to a new line
						quad.x = x;
						quad.y += fontmap_char_space_y;
						slot = 0;
						continue;
					}
					
					//If the current one is a printable character (it doesn't include space)
					if( (int)*c >= 33 && (int)*c <= 126 ){
						//If the next one isnt \0 and is not a space
						if( *(c+1) != 0 && *(c+1) != ' ' ){
							//We need to print a `dash`
							SDL_RenderCopy(raw_renderer, sprites[(int)'-']->raw_texture, &sprites[(int)'-']->clip, &quad);

							quad.x = x;
							quad.y += fontmap_char_space_y;

							//And we need to print the one that should be printed but in the next line
							SDL_RenderCopy(raw_renderer, sprites[(int)*c]->raw_texture, &sprites[(int)*c]->clip, &quad);
							quad.x += fontmap_char_space_x;
							slot = 1; //Because we printed 2 (`dash` and the current one)
						}else{
							//If the next one (after the current one) is a space then we don't need `dash`
							SDL_RenderCopy(raw_renderer, sprites[(int)*c]->raw_texture, &sprites[(int)*c]->clip, &quad);
							quad.x = x;
							quad.y += fontmap_char_space_y;
							slot = 0;
						}
					}

				}else{
					//If it is not a space, then we render (if it is a space, we just increment x)
					if( *c != ' ' ){
						SDL_RenderCopy(raw_renderer, sprites[(int)*c]->raw_texture, &sprites[(int)*c]->clip, &quad);
					}
					//If it is a new line and the first character on that line is a space, don't print and "re-use" that space
					if( slot == 1 && *c == ' ' ){
						slot--;
					}else{
						//If it is not a space, increase x
						quad.x += fontmap_char_space_x;
					}
				}
			}
		}

		StaticText* FontManager::CreateStaticText(const char* text, const int x, const int y, const int max_slots){
			int text_size = strlen(text);
			std::vector<sprite_info*> vector;
			vector.reserve( text_size + (int)std::ceil(((float)text_size/max_slots)) );
			
			SDL_Rect quad = {x, y, fontmap_char_space_x, fontmap_char_space_y};
			int slot = 0;
			/* This procedure is the same as the one in RenderMultipleText. For info go to that function and for modifications, must be done on both */
			for(const char* c = text; *c; ++c){
				slot++;
				if( slot == max_slots ){
					if( *(c-1) == ' ' ){
						--c;
						quad.x = x;
						quad.y += fontmap_char_space_y;
						slot = 0;
						continue;
					}
					if( *c == ' ' ){
						quad.x = x;
						quad.y += fontmap_char_space_y;
						slot = 0;
						continue;
					}
					if( (int)*c >= 33 && (int)*c <= 126 ){
						if( *(c+1) != 0 && *(c+1) != ' ' ){
							vector.push_back(new sprite_info(sprites[(int)'-']->raw_texture, sprites[(int)'-']->clip, quad.x, quad.y));
							quad.x = x;
							quad.y += fontmap_char_space_y;
							vector.push_back(new sprite_info(sprites[(int)*c]->raw_texture, sprites[(int)*c]->clip, quad.x, quad.y));
							quad.x += fontmap_char_space_x;
							slot = 1;
						}else{
							vector.push_back(new sprite_info(sprites[(int)*c]->raw_texture, sprites[(int)*c]->clip, quad.x, quad.y));
							quad.x = x;
							quad.y += fontmap_char_space_y;
							slot = 0;
						}
					}
				}else{
					if( *c != ' ' ){
						vector.push_back(new sprite_info(sprites[(int)*c]->raw_texture, sprites[(int)*c]->clip, quad.x, quad.y));
					}
					if( slot == 1 && *c == ' ' ){
						slot--;
					}else{
						quad.x += fontmap_char_space_x;
					}
				}
			}

			return new StaticText(raw_renderer, vector, max_slots, fontmap_char_space_x, fontmap_char_space_y);
		}
	}
}