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

		protected:
			
			SDL_Rect square;
		private:
		};
	}
}

#endif