#include "stdafx.h"
#ifndef RPGLIB_ENGINEINCLUDE_H
#define RPGLIB_ENGINEINCLUDE_H

namespace Osaka{
	namespace Engine{
		//This is used so that TextureManager:RenderSprite isn't obligated to put all the parameters that Texture:Render has
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