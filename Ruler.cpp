 #include "stdafx.h"

#include "Ruler.h"

namespace Osaka{
	namespace RPGLib{
		Ruler::Ruler(int width, int height){
			max_width = width;
			max_height = height;

			//These are always 0
			x_top_left_corner = 0;
			y_top_left_corner = 0;

		}
		Ruler::~Ruler(){
		}
		void Ruler::_delete(){

		}
	}
}