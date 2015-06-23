 #include "stdafx.h"

#ifndef RPGLIB_SQUARE_H
#define RPGLIB_SQUARE_H

#include "Drawable.h"

namespace Osaka{
	namespace RPGLib{

		class Square : public Drawable{
		public:
			Square(SDL_Renderer* raw_renderer);
			~Square();
			
			void Draw() override;
			void DrawBlend() override;

			SDL_Rect square;
		protected:
			
		private:
		};
	}
}

#endif