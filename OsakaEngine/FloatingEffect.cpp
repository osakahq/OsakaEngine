 #include "stdafx.h"

#include "Drawable.h"
#include "DrawableTexture.h"
#include "Utils.h"
#include "EventHandler.h"
#include "EventArgs.h"
#include "TimeManager.h"
#include "Utils.h"
#include "FloatingEffect.h"

namespace Osaka{
	namespace RPGLib{

		FloatingEffect::FloatingEffect(TimeManager* timerm) : Modifier(false, true){
			this->timerm = timerm;
		}
		
		FloatingEffect::~FloatingEffect(){
			timerm = NULL;
		}
		bool FloatingEffect::__Drawable_Attach(Drawable* obj, DrawableModifierArgs& args){
			if( Modifier::__Drawable_Attach(obj, args) ) {
				DrawableModFloatingArgs& fargs = dynamic_cast<DrawableModFloatingArgs&>(args);
				floatings.insert(std::make_pair(obj, floating_info(fargs.wiggleY)));
				return true;
			}
			return false;
		}
		void FloatingEffect::__Drawable_Deattach(Drawable* obj){
			Modifier::__Drawable_Deattach(obj);
			floatings.erase(obj);
		}

		void FloatingEffect::__Drawable_Mod(Drawable& obj){
			floating_info& info = floatings[&obj];
			
			float distance_to_travel = (info.wiggleY - info.traveled_y); //5 - 0 * 0.032 = 0.175

			/* We need this so that at first it doesnt go too fast */
			float easing_easing_delta = info.traveled_y/info.wiggleY;
			if( easing_easing_delta < 0.2f )
				easing_easing_delta = 0.2f; //If we don't do this it will never move if info.traveled_y = 0
			distance_to_travel *= (easing_delta*easing_easing_delta);
			
			info.traveled_y += distance_to_travel;

			int traveled_y = static_cast<int>(info.traveled_y);
			//if [0].175 > 0. if [1].175 > 0
			if( traveled_y > info.pixels_to_travel_y ){
				//y -= 1 - 0
				if( info.up ){	obj.quad.y -= info.pixels_to_travel_y - traveled_y; }
				else{			obj.quad.y += info.pixels_to_travel_y - traveled_y; }
				info.pixels_to_travel_y = traveled_y;
			}

			//if [1].175 >= 5
			//We need to add 0.1 because it never reaches 5
			if( info.traveled_y+0.1f >= info.wiggleY ){
				info.pixels_to_travel_y = 0;
				info.traveled_y = 0;
				info.up = (info.up) ? false : true;
			}
		}
		void FloatingEffect::_Update(){
			//If I want a slower/faster motion then I should divide/multiply the result of easing_delta
			easing_delta = (static_cast<float>(timerm->GetDelta()) / 100.0f) / 6.5f;
			//easing_delta = 0.035;
		}
		
		void FloatingEffect::Reset(){
			
		}
	}
}