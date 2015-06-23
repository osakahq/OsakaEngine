 #include "stdafx.h"

#include "Image.h"

namespace Osaka{
	namespace RPGLib{
		Image::Image(SDL_Renderer* raw_renderer, sprite_info* info) : DrawableTexture(raw_renderer, info){
			
		}
		Image::~Image(){

		}

		void Image::Draw(){
			//Inexpensive draw
			SDL_RenderCopy(raw_renderer, info->raw_texture, &info->clip, &info->quad);
		}
	}
}