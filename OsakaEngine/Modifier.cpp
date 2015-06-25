 #include "stdafx.h"

#include "Drawable.h"
#include "Modifier.h"

namespace Osaka{
	namespace RPGLib{

		Modifier::Modifier(bool ne, bool nt) : need_ex(ne), need_transparency(nt){
			forever_repeat = false;
			times_repeat = 1;
			current_loop = 0;
			loop_was_done = false;

			active = true;
		}
		Modifier::~Modifier(){
			for(auto it = objs.begin(); it != objs.end(); ++it){
				it->second->__Mod_Need(need_ex, need_transparency, false);
				it->second->__Mod_Deattach(this);
			}
		}
		void Modifier::SetRepetitions(int times_repeat, bool forever_repeat){
			this->forever_repeat = forever_repeat;
			this->times_repeat = times_repeat;
		}

		void Modifier::Update(){
			if( !active )
				return;
			if( loop_was_done ){
				Reset();
				/* This has to be after Reset() so we can actually identify when: 
				 * Reset is being called when a loop is done or when owner calls it (Restart) */
				loop_was_done = false;
			}
			//It deattaches itself in the next Update.
			if( forever_repeat == false && current_loop >= times_repeat ){
				active = false;
				//Since it reached times_repeat, then it will always deattach itself
				for(auto it = objs.begin(); it != objs.end(); ++it){
					it->second->__Mod_Need(need_ex, need_transparency, false);
					it->second->__Mod_Deattach(this);
				}
				objs.clear();
				return;
				
			}else{
				//If forever repeat == true and current_loop is lesser than times_repeat
				_Update();
			}
		}
		
		void Modifier::Restart(){
			loop_was_done = false;
			current_loop = 0;
			active = true;
			Reset();
		}
		void Modifier::OneLoop(){
			++current_loop;
			/* See header file for the explanation on why we don't call `Reset` */
			loop_was_done = true;
		}

		bool Modifier::__Drawable_Attach(Drawable* obj, DrawableModifierArgs& args){
			//Only when the obj doesn't exists in the map
			if( objs.find(obj) == objs.end() ){
				obj->__Mod_Need(need_ex, need_transparency, true);
				objs[obj] = obj;
				return true;
			}
			//This return value should be checked if base class overrides this function.
			return false;
		}
		void Modifier::__Drawable_Deattach(Drawable* obj){
			obj->__Mod_Need(need_ex, need_transparency, false);
			objs.erase(obj);
		}
	}
}