 #include "stdafx.h"

#include "Hiccups.h"
namespace Osaka{
	namespace RPGLib{

		Hiccups::Hiccups(){
			fills_in_array.reserve(15);
		}

		Hiccups::~Hiccups(){

		}

		void Hiccups::Frame(const int frame_ms){
#ifdef _DEBUG
			if( frame_ms < 0 ){
				throw std::exception("[Hiccups] frame_ms cannot be lesser than 0.");
			}
#endif
			if( frame_ms >= HICCUPS_MAX_ARRAY ){
				printf("[Hiccups] Current frame is longer than HICCUPS_MAX_ARRAY < [%d]\n", frame_ms);
				return;
			}
			if( hiccups_array[frame_ms].quantity == 0 ){
				fills_in_array.push_back(frame_ms);
			}
			hiccups_array[frame_ms].quantity++;
		}
		void Hiccups::EndSet(const float average_ms){
			const float comparison = (average_ms * 0.7f)*2;
			bool printed = false;
			for(unsigned int i = 0; i < fills_in_array.size(); ++i){
				if( fills_in_array[i] > 1 && fills_in_array[i] >= comparison ){
					if( printed == false ){
						printf("[Hiccups]");
					}
					printed = true;
					printf(" %d[%dms] |", hiccups_array[fills_in_array[i]].quantity, fills_in_array[i]);
				}
				hiccups_array[fills_in_array[i]].quantity = 0;
			}
			fills_in_array.clear();
			if( printed ){
				printf("| Average was: %fms\n", average_ms);
			}
		}
	}
}