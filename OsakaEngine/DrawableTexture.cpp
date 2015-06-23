 #include "stdafx.h"

#include "Canvas.h"
#include "DrawableTexture.h"

namespace Osaka{
	namespace RPGLib{
		DrawableTexture::DrawableTexture(SDL_Renderer* raw_renderer, sprite_info* info) : Drawable(raw_renderer){
			if( info == NULL ){
				throw std::exception("[DrawableTexture] info cannot be null.");
			}
			this->info = info;
		}
		DrawableTexture::~DrawableTexture(){
			if( info != NULL )
				delete info;
			info = NULL;
		}

		void DrawableTexture::DrawBlend(){
			throw std::exception("[DrawableTexture] Don't call this function");
		}

	}
}