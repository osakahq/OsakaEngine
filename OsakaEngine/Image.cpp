 #include "stdafx.h"

#include "Image.h"

namespace Osaka{
	namespace RPGLib{
		Image::Image(SDL_Renderer* raw_renderer, SDL_Texture* _raw_texture, SDL_Rect _clip) 
			: DrawableTexture(raw_renderer, _raw_texture, _clip)
		{
			
		}
		Image::~Image(){

		}

		void Image::_Draw(){
			SDL_RenderCopy(raw_renderer, raw_texture, &clip, &quad);
		}
		void Image::_DrawTransparency(){
			SDL_SetTextureAlphaMod(raw_texture, rgba.a);
			SDL_RenderCopy(raw_renderer, raw_texture, &clip, &quad);
			SDL_SetTextureAlphaMod(raw_texture, 255); //Reset
		}
		
	}
}