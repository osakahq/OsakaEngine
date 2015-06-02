 #include "stdafx.h"
#ifndef RPGLIB_HICCUPS_H
#define RPGLIB_HICCUPS_H

#define HICCUPS_MAX_ARRAY 60

namespace Osaka{
	namespace RPGLib{

		struct HiccupsInfo{
			HiccupsInfo(){
				quantity = 0;
			}
			int quantity;
		};

		class Hiccups{
		public:
			Hiccups();
			~Hiccups();

			void _delete();

			/* This is called after `sdl->Present()` in EApplication. */
			void Frame(Uint32 frame_ms);
			/* This is called inside before present */
			void EndSet(float average_ms);
		private:

			std::vector<int> fills_in_array; //These is a list of which slots are used
			HiccupsInfo hiccups_array[HICCUPS_MAX_ARRAY]; //index is time in ms (not the position of the frame)
		};
	}
}

#endif