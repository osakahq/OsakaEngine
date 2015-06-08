 #include "stdafx.h"

#ifndef RPGLIB_DRAWABLETEXTURE_H
#define RPGLIB_DRAWABLETEXTURE_H

#include "Drawable.h"

namespace Osaka{
	namespace RPGLib{

		class DrawableTexture : public Drawable{
		public:
			DrawableTexture(SDL_Renderer* raw_renderer, sprite_info* info);
			virtual ~DrawableTexture();
			/* OWNER. Raw pointer */
			sprite_info* info;

		protected:
			
		private:
		};
	}
}

#endif