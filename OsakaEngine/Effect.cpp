 #include "stdafx.h"

#include "Drawable.h"
#include "Effect.h"

namespace Osaka{
	namespace RPGLib{

		Effect::Effect(const std::string& _id) : id(_id){
			
			repeat = true;
			times_repeat = 1;
			current_loop = 0;
			deattach = false;
			isActive = true;
			raw_obj = NULL;
		}
		Effect::~Effect(){
#ifdef _DEBUG
			_CHECKDELETE("Effect");
#endif
			if( raw_obj != NULL ){
				//It's okay to check because when drawable is being deleted, it announces to all effects.
				raw_obj->RemoveEffect(this->id); //This will call `effect->Deattach()`
			}
			raw_obj = NULL;
		}

		void Effect::Attach(Drawable* obj){
			if( raw_obj != NULL ){
				throw std::exception("[Effect] Effect cannot have 2 or more objects at the same time.");
			}
			this->raw_obj = obj;
		}
		void Effect::Deattach(){
			raw_obj = NULL;
		}
		void Effect::Update(){

		}
		
		void Effect::Reset(){
			isActive = true;
			current_loop = 0;
		}
		void Effect::OneLoopDone(){
			//Right now we aren't using `repeat` var.
			++current_loop;
			Reset();
			if( current_loop >= times_repeat ){
				isActive = false;
				if( deattach )
					raw_obj->RemoveEffect(this->id);
			}
		}
	}
}