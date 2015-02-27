 #include "stdafx.h"

#include "rpglib_include.h"
#include "StaticText.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		StaticText::StaticText(SDL_Renderer& _renderer, std::vector<sprite_info*>& sprites, int max_slots, int space_x, int space_y) 
			: raw_renderer(_renderer), fontmap_char_space_x(space_x), fontmap_char_space_y(space_y){
			if( sprites.size() <= 1 )
				throw std::exception("[StaticText] sprites size is <= 1");

			this->sprites = sprites;
			this->max_slots = max_slots;
		}
		StaticText::~StaticText(){

		}
		void StaticText::_delete(){
			for( auto it = sprites.begin(); it != sprites.end(); ++it){
				delete *it;
			}
			sprites.clear();
			//raw_renderer = NULL; is a Reference(&)
		}

		void StaticText::Render(){
			for( auto it = sprites.begin(); it != sprites.end(); ++it){
				SDL_RenderCopy(&raw_renderer, (*it)->raw_texture, &(*it)->clip, &(*it)->quad);
			}
		}
		
		void StaticText::Change(const int x, const int y){
			int valx = x - sprites.front()->quad.x;
			int valy = y - sprites.front()->quad.y;
			//We change the coordinates relative to the current ones
			for( auto it = sprites.begin(); it != sprites.end(); ++it){
				(*it)->quad.x += valx;
				(*it)->quad.y += valy;
			}
		}
	}
}