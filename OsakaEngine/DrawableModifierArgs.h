 #include "stdafx.h"
#ifndef RPGLIB_DRAWABLEMODIFERARGS_H
#define RPGLIB_DRAWABLEMODIFERARGS_H
#include "rpglib_include.h"
namespace Osaka{
	namespace RPGLib{
		
		/* This is passed down to Modifier (derived class) 
		 * See Drawable for more info. */
		class DrawableModifierArgs{
		public:
			//drawable_mod_args(){}
			virtual ~DrawableModifierArgs(){}
		};
	}
}

#endif