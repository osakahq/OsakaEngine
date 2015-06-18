 #include "stdafx.h"
#ifndef RPGLIB_RULER_H
#define RPGLIB_RULER_H

namespace Osaka{
	namespace RPGLib{

		class Ruler{
		public:
			Ruler(int width, int height);
			~Ruler();

			int x_top_left_corner;
			int y_top_left_corner;

			//Window size
			int max_width;
			int max_height;

		private:
		};
	}
}

#endif