 #include "stdafx.h"

#ifndef RPGLIB_DRAWABLETEXTURE_H
#define RPGLIB_DRAWABLETEXTURE_H

#include "Drawable.h"

namespace Osaka{
	namespace RPGLib{

		class DrawableTexture : public Drawable{
		public:
			DrawableTexture(SDL_Renderer* raw_renderer, SDL_Texture* _raw_texture, SDL_Rect _clip);
			virtual ~DrawableTexture();
			
			const SDL_Rect clip;
			/* NOT Owner. */
			SDL_Texture* raw_texture;
		protected:
			
		};
	}
}

#endif