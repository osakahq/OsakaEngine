 #include "stdafx.h"

#include "Ruler.h"

namespace Osaka{
	namespace RPGLib{
		Ruler::Ruler(int width, int height) 
			: max_width(width), max_height(height),
			x_top_left_corner(0), y_top_left_corner(0)
		{
			
		}
		Ruler::~Ruler(){

		}
		
		int Ruler::MidX(int xsize){
			return static_cast<int>(std::floor(max_width / 2) - std::floor(xsize / 2));
		}
		int Ruler::MidY(int ysize){
			return static_cast<int>(std::floor(max_height / 2) - std::floor(ysize / 2));
		}
	}
}