 #include "stdafx.h"

#include "Square.h"

namespace Osaka{
	namespace RPGLib{
		Square::Square(SDL_Renderer* raw_renderer) : Drawable(raw_renderer){
			
		}
		Square::~Square(){

		}

		void Square::_Draw(){
			SDL_SetRenderDrawColor(raw_renderer, rgba.r, rgba.g, rgba.b, rgba.a);
			SDL_RenderFillRect(raw_renderer, &quad);
		}
		void Square::_DrawTransparency(){
			SDL_SetRenderDrawColor(raw_renderer, rgba.r, rgba.g, rgba.b, rgba.a);
			SDL_SetRenderDrawBlendMode(raw_renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(raw_renderer, &quad);
			SDL_SetRenderDrawBlendMode(raw_renderer, SDL_BLENDMODE_NONE);
		}
		
	}
}