 #include "stdafx.h"

#ifndef RPGLIB_IMAGE_H
#define RPGLIB_IMAGE_H

#include "Drawable.h"

namespace Osaka{
	namespace RPGLib{

		class Image : public Drawable{
		public:
			Image(SDL_Renderer* raw_renderer, sprite_info& info);
			~Image();
			
			void Draw() override;
		protected:
			
		private:
		};
	}
}

#endif