 #include "stdafx.h"

#include "Drawable.h"
#include "Modifier.h"

namespace Osaka{
	namespace RPGLib{

		Modifier::Modifier(){
			forever_repeat = false;
			times_repeat = 1;
			current_loop = 0;
			deattach = false;
		}
		Modifier::~Modifier(){
			for(auto it = objs.begin(); it != objs.end(); ++it){
				it->second->__Mod_Deattach(this);
			}
		}
		void Modifier::Set(int times_repeat, bool deattach, bool forever_repeat){
			this->forever_repeat = forever_repeat;
			this->times_repeat = times_repeat;
			this->deattach = deattach;
		}

		void Modifier::Update(){
			//It deattaches itself in the next Update.
			if( forever_repeat == false && current_loop >= times_repeat ){
				if( deattach ){
					for(auto it = objs.begin(); it != objs.end(); ++it){
						it->second->__Mod_Deattach(this);
					}
					objs.clear();
					return;
				}
			}else{
				//If forever repeat == true and current_loop is lesser than times_repeat
				_Update();
			}
		}
		
		void Modifier::Restart(){
			current_loop = 0;
			Reset();
		}
		void Modifier::OneLoop(){
			++current_loop;
			Reset();
		}

		bool Modifier::__Drawable_Attach(Drawable* obj){
			//Only when the obj doesn't exists in the map
			if( objs.find(obj) == objs.end() ){
				objs[obj] = obj;
				return true;
			}
			//This return value should be checked if base class overrides this function.
			return false;
		}
		void Modifier::__Drawable_Deattach(Drawable* obj){
			objs.erase(obj);
		}
	}
}