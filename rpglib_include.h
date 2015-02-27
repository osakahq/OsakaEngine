 #include "stdafx.h"
#ifndef RPGLIB_RPGLIBINCLUDE_H
#define RPGLIB_RPGLIBINCLUDE_H

namespace Osaka{
	namespace RPGLib{
		struct TransitionType{
			TransitionType(){}
			enum Value{
				SWITCH, STACK	
			};
		};

		/* This is an optimized way to render many sprites instead of each frame looking up inside the unordered_maps 
		 * This is created in TextureManager */
		struct sprite_info{
			sprite_info(SDL_Texture* t, SDL_Rect& _clip) 
				: raw_texture(t), clip(_clip)
			{
				quad.x = quad.y = 0;
				w = quad.w = clip.w;
				h = quad.h = clip.h;
				if( t == NULL ){
					throw std::exception("[sprite_info] Constructor > Raw texture is NULL");
				}
			}
			SDL_Texture* raw_texture;
			const SDL_Rect clip;
			SDL_Rect quad;

			//In case, you only need w/h
			int w;
			int h;
		};

		//typedef std::shared_ptr<sprite_info> sprite_infoPTR;
	}
}

#endif