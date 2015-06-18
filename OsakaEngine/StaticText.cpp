 #include "stdafx.h"

#include "rpglib_include.h"
#include "StaticText.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		StaticText::StaticText(SDL_Renderer* _renderer, std::vector<sprite_info*>& sprites, int max_slots, int space_x, int space_y) 
			: raw_renderer(_renderer), fontmap_char_space_x(space_x), fontmap_char_space_y(space_y){
			if( sprites.size() < 1 )
				throw std::exception("[StaticText] sprites size is < 1");

			this->sprites = sprites;
			this->max_slots = max_slots;
		}
		StaticText::~StaticText(){
			//If sprite_info had _delete() function, it should be called before `delete *it;`
			for(unsigned int i = 0; i < sprites.size(); ++i){
				delete sprites[i];
			}
			sprites.clear();
			raw_renderer = NULL;
		}
		
		void StaticText::Render(){
			/* Talvez cuando ponga la funcion para que StaticText se pueda modificar, poner un array para el tight loop */
			for(unsigned int i = 0; i < sprites.size(); ++i){
				SDL_RenderCopy(raw_renderer, sprites[i]->raw_texture, &sprites[i]->clip, &sprites[i]->quad);
			}
		}
		
		void StaticText::Change(const int x, const int y){
			int valx = x - sprites.front()->quad.x;
			int valy = y - sprites.front()->quad.y;
			//We change the coordinates relative to the current ones
			for(unsigned int i = 0; i < sprites.size(); ++i){
				sprites[i]->quad.x += valx;
				sprites[i]->quad.y += valy;
			}
		}
	}
}