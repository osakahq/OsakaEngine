 #include "stdafx.h"

#ifndef RPGLIB_IMAGE_H
#define RPGLIB_IMAGE_H

#include "DrawableTexture.h"

namespace Osaka{
	namespace RPGLib{

		class Image : public DrawableTexture{
		public:
			Image(SDL_Renderer* raw_renderer, SDL_Texture* _raw_texture, SDL_Rect _clip);
			~Image();
			
			void _Draw() override;
			void _DrawTransparency() override;
		protected:
			
		private:
		};
	}
}

#endif