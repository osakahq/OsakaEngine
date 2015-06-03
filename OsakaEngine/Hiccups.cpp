 #include "stdafx.h"

#include "Hiccups.h"
namespace Osaka{
	namespace RPGLib{

		Hiccups::Hiccups(){
			fills_in_array.reserve(15);
		}

		Hiccups::~Hiccups(){

		}

		void Hiccups::_delete(){

		}

		void Hiccups::Frame(const Uint32 frame_ms){
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
			for(auto it = fills_in_array.begin(); it != fills_in_array.end(); ++it ){
				if( *it > 1 && *it >= comparison ){
					if( printed == false ){
						printf("[Hiccups]");
					}
					printed = true;
					printf(" %d[%dms] |", hiccups_array[*it].quantity, *it);
				}
				hiccups_array[*it].quantity = 0;
			}
			fills_in_array.clear();
			if( printed ){
				printf("| Average was: %fms\n", average_ms);
			}
		}
	}
}