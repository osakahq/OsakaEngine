 #include "stdafx.h"

#include "rpglib_include.h"
#include "Canvas.h"
#include "DrawableTexture.h"

namespace Osaka{
	namespace RPGLib{
		DrawableTexture::DrawableTexture(SDL_Renderer* raw_renderer, SDL_Texture* _raw_texture, SDL_Rect _clip) 
			: Drawable(raw_renderer), clip(_clip)
		{
			raw_texture = _raw_texture;
			quad.x = quad.y = 0;
			quad.w = clip.w;
			quad.h = clip.h;
		}
		DrawableTexture::~DrawableTexture(){
			raw_texture = NULL;
		}

	}
}