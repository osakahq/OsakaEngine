 #include "stdafx.h"

#include "EventArgs.h"
#include "EventHandler.h"
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
			oneLoop = new Component::EventHandler();
		}
		Modifier::~Modifier(){
			for(auto it = objs.begin(); it != objs.end(); ++it){
				it->second->__Mod_Need(need_ex, need_transparency, false);
				it->second->__Mod_Deattach(this);
			}
			delete oneLoop; oneLoop = NULL;
		}
		void Modifier::SetRepetitions(int times_repeat, bool forever_repeat){
			this->forever_repeat = forever_repeat;
			this->times_repeat = times_repeat;
		}

		void Modifier::Update(){
			if( !active )
				return;

			/* When current_loop changes value (++), `loop_was_done` is always true. */
			if( loop_was_done ){
				Reset(loop_was_done); //true
				loop_was_done = false;

				//It deattaches itself in the next Update.
				if( forever_repeat == false && current_loop >= times_repeat ){
					active = false;
					//Since it reached times_repeat, then it will always deattach itself
					for(auto it = objs.begin(); it != objs.end(); ++it){
						it->second->__Mod_Need(need_ex, need_transparency, false);
						it->second->__Mod_Deattach(this);
					}
					objs.clear();
					ModifierEventArgs* args = new ModifierEventArgs(true);
					oneLoop->Raise(*args);
					delete args;
				}else{
					//If forever repeat == true and current_loop is lesser than times_repeat
					ModifierEventArgs* args = new ModifierEventArgs();
					oneLoop->Raise(*args);
					delete args;
				}
			}else{
				_Update();
			}
		}
		
		void Modifier::Restart(){
			loop_was_done = false;
			current_loop = 0;
			active = true;
			Reset(false);
		}
		void Modifier::OneLoop(){
			++current_loop;
			/* See header file for the explanation on why we don't call `Reset` */
			loop_was_done = true;
		}

		void Modifier::__Drawable_Attach(Drawable* obj, DrawableModifierArgs& args){
			//Only when the obj doesn't exists in the map
			if( objs.find(obj) == objs.end() ){
				obj->__Mod_Need(need_ex, need_transparency, true);
				objs[obj] = obj;
				_Attach(obj, args);
			}
		}
		void Modifier::__Drawable_Deattach(Drawable* obj){
			obj->__Mod_Need(need_ex, need_transparency, false);
			objs.erase(obj);
			_Deattach(obj);
		}

		void Modifier::_Attach(Drawable* obj, DrawableModifierArgs& args){}
		void Modifier::_Deattach(Drawable* obj){}
	}
}