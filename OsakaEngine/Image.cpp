 #include "stdafx.h"

#include "Image.h"

namespace Osaka{
	namespace RPGLib{
		Image::Image(SDL_Renderer* raw_renderer, sprite_info& info) : Drawable(raw_renderer){
			this->info = &info;
		}
		Image::~Image(){

		}

		void Image::Draw(){
			//TODO: falta mucho.. si tiene angle? alpha? etc.
			//SDL_SetRenderDrawBlendMode(raw_renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderCopy(raw_renderer, info->raw_texture, &info->clip, &info->quad);
			//SDL_SetRenderDrawBlendMode(raw_renderer, SDL_BLENDMODE_NONE);
		}
	}
}