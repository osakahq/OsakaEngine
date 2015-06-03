#include "stdafx.h"
#ifndef RPGLIB_ENGINEINCLUDE_H
#define RPGLIB_ENGINEINCLUDE_H

namespace Osaka{
	namespace Engine{
		/* Use `render_info` in `rpglib_include.h` to render with optimization. Do not use this.
		 * This struct is used in SDL Render, to save time not settings some variables. */
		struct render_info_ex{
			render_info_ex(int _x, int _y,double an, SDL_Point* cen, SDL_RendererFlip fli) : 
				x(_x), y(_y), angle(an), center(cen), flip(fli)
				{}
			int x;
			int y; 
			double angle;
			SDL_Point* center; 
			SDL_RendererFlip flip;
		};
		struct RGBA_HEX{
			RGBA_HEX(){}
			RGBA_HEX(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a):r(_r),g(_g),b(_b),a(_a){}
			Uint8 r;
			Uint8 g;
			Uint8 b;
			Uint8 a;
		};
		extern RGBA_HEX EMPTYRGBA_HEX;

		struct RGB_HEX{
			RGB_HEX(){}
			Uint8 r;
			Uint8 g;
			Uint8 b;
		};
		extern RGB_HEX EMPTYRGB_HEX;
	}
}
#endif