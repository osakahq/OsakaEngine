 #include "stdafx.h"
#ifndef RPGLIB_RULER_H
#define RPGLIB_RULER_H

namespace Osaka{
	namespace RPGLib{

		class Ruler{
		public:
			Ruler(int width, int height);
			~Ruler();

			const int x_top_left_corner;
			const int y_top_left_corner;

			//Window size
			const int max_width;
			const int max_height;

			int MidX(int xsize);
			int MidY(int ysize);
		private:
		};
	}
}

#endif