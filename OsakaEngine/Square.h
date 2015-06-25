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
			
			void _Draw() override;
			void _DrawTransparency() override;

		protected:
			
		private:
		};
	}
}

#endif