 #include "stdafx.h"

#include "Drawable.h"
#include "Effect.h"

namespace Osaka{
	namespace RPGLib{

		Effect::Effect(){
			id = "_effect"; //this should be changed in derived class

			repeat = true;
			times_repeat = 1;
			current_loop = 0;
			deattach = false;
			isActive = true;
		}
		Effect::~Effect(){
#ifdef _DEBUG
			_CHECKDELETE("Effect");
#endif
			//there is no need for `obj = nullptr;`
		}

		void Effect::Attach(DrawablePTR& obj){
			this->obj = obj;
		}
		void Effect::Update(){

		}
		void Effect::ChangeId(std::string id){
			this->id = id;
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
					obj->RemoveEffect(this->id);
			}
		}
	}
}