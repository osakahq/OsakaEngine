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
		void FloatingEffect::_Attach(Drawable* obj, DrawableModifierArgs& args){
			//This is only called if the obj was succesfully inserted in map (base class)
			DrawableModFloatingArgs& fargs = dynamic_cast<DrawableModFloatingArgs&>(args);
			floatings.insert(std::make_pair(obj, floating_info(fargs.wiggleY, fargs.percentage_delta)));
		}
		void FloatingEffect::_Deattach(Drawable* obj){
			floatings.erase(obj);
		}

		void FloatingEffect::__Drawable_Mod(Drawable& obj){
			floating_info& info = floatings[&obj];
			
			/* Since we are counting how many pixels we are moving, we move relative to that.
			 * We don't move store the initial position of the object */

			float distance_to_travel = (info.wiggleY - info.traveled_y); //5 - 0 = 5

			/* We need this so that at first it doesnt go too fast at the beginning */
			float easing_delta = info.traveled_y / info.wiggleY;
			if( easing_delta < 0.2f ){
				//If we don't do this it will never move if info.traveled_y = 0, because of the multiplication
				easing_delta = 0.2f;
			}

			//5 *= ((0.16*0.25)*0.2) = 0.032
			distance_to_travel *= ((delta * info.percentage_delta) * easing_delta);
			
			//0 += 0.032
			info.traveled_y += distance_to_travel;

			//traveled_y = [0].032
			int traveled_y = static_cast<int>(info.traveled_y);
			//if [0].175 > 0. if [1].175 > 0
			if( traveled_y > info.pixels_traveled_y ){
				//y -= 1 - 0
				if( info.up ){	obj.quad.y += info.pixels_traveled_y - traveled_y; }
				else{			obj.quad.y -= info.pixels_traveled_y - traveled_y; }
				//We count how many pixels we have moved
				info.pixels_traveled_y = traveled_y;

				//"initial y" == "current y" means we are at the initial y (middle y)
				if( info.phase == 2 && info.middle_pixels_y == info.pixels_traveled_y ){
					//info.phase=2 means we are going up (down was rechead)
					this->OneLoop();
					info.phase = 0;
				}
			}

			//if [1].175 >= 5
			//We need to add 0.1 because it never reaches 5
			if( info.traveled_y + 0.1f >= info.wiggleY ){
				//This check is only to switch directions: up / down
				info.pixels_traveled_y = 0;
				info.traveled_y = 0;
				info.up = (info.up) ? false : true;

				++info.phase;
			}
		}
		void FloatingEffect::_Update(){
			//If I want a slower/faster motion then I should divide/multiply the result of easing_delta
			delta = static_cast<float>(timerm->GetDelta()) / 100.f;
			//easing_delta = 0.035;
		}
		
		void FloatingEffect::Reset(bool loop_finished){
			/* Because of the nature of the effect, 1 loop is done when we are at the middle meaning
			 * The object is left with the initial y */
			if( loop_finished == false ){
				//If `loop_was_done` is false, it means owner called Restart
				for(auto it = floatings.begin(); it != floatings.end(); ++it){
					//If the object actually moved, we need to substract those to the current y.
					/* if "current y" is different than "initial y" */
					if( it->second.pixels_traveled_y != it->second.middle_pixels_y ){
						//We need to modify the object here.
						if( it->second.up ) //If we are up, we need to go down (-=)
							it->first->quad.y -= it->second.pixels_traveled_y;
						else
							it->first->quad.y += it->second.pixels_traveled_y;

						it->second.Reset();
					}
				}
			}
		}
	}
}