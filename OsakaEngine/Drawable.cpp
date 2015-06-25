 #include "stdafx.h"

#include "Modifier.h"
#include "DrawableModifierArgs.h"
#include "Drawable.h"

namespace Osaka{
	namespace RPGLib{

		Drawable::Drawable(SDL_Renderer* raw_renderer){
			this->raw_renderer = raw_renderer;
			rgba.r = 255;
			rgba.g = 0;
			rgba.b = 169;
			rgba.a = 255;

			angle = 0;
			flip = SDL_FLIP_NONE;
			quad.h = quad.w = center_point.y = center_point.x = quad.y = quad.x = 0;

			need_ex = need_transparency = 0;

			has_list_changed = true;
			temp_stack_items = 0;

			draw_func = std::bind(&Drawable::_Draw, this);
		}
		Drawable::~Drawable(){
			//It has to announce so the effect deattach themselves.
			for(unsigned int i = 0; i < stack_effects.size(); ++i){
				stack_effects[i]->__Drawable_Deattach(this);
			}
			raw_renderer = NULL;
		}

		void Drawable::Update(){
			if( has_list_changed ){
				temp_stack_items = stack_effects.size();
				std::copy(stack_effects.begin(), stack_effects.end(), temp_stack);
			}
			for(int i = 0; i < temp_stack_items; ++i){
				temp_stack[i]->__Drawable_Mod(*this);
			}
		}

		void Drawable::Draw(){
			draw_func();
		}
		void Drawable::__Mod_Need(bool ex, bool transparency, bool attach){
			if( attach ){
				if( ex ) ++need_ex;
				if( transparency ) ++need_transparency;
			}else{
				if( ex ) --need_ex;
				if( transparency ) --need_transparency;
			}
			if( ex || transparency ) SetDrawFunc();
		}
		
		void Drawable::SetDrawFunc(){
			/* If drawable has a custom function then override this. 
			 * First check derived vars then if none, call this base function as default */
			if( need_ex == 0 && need_transparency == 0 ){
				draw_func = std::bind(&Drawable::_Draw, this);
			}else if( need_ex == 0 && need_transparency > 0 ){
				draw_func = std::bind(&Drawable::_DrawTransparency, this);
			}else if( need_ex > 0 && need_transparency == 0 ){
				draw_func = std::bind(&Drawable::_DrawEx, this);
			}else{
				//both are > 0
				draw_func = std::bind(&Drawable::_DrawTransparencyEx, this);
			}
		}
		void Drawable::AddMod(Modifier* effect){
			AddMod(effect, EmptyDrawableModifierArgs);
		}
		void Drawable::AddMod(Modifier* effect, DrawableModifierArgs& args){
			if( effects_in_list.find(effect) != effects_in_list.end() ){
				throw std::exception("[Drawable] Effect id already exists.");
			}
			effects_in_list[effect] = true;
			stack_effects.push_back(effect);
			/* Raw pointer (raw_pointer) It's okay. When the object is destroyed, it notifies the effect. */
			effect->__Drawable_Attach(this, args);
			has_list_changed = true;
		}
		
		void Drawable::RemoveMod(Modifier* effect){
			auto it = std::find(stack_effects.begin(), stack_effects.end(), effect);
			//If it doesn't exists, who cares.
			if( it != stack_effects.end() ){
				(*it)->__Drawable_Deattach(this);

				stack_effects.erase(it);
				effects_in_list.erase(effect);
				has_list_changed = true;
			}
		}
		void Drawable::RemoveMods(){
			//vector has the same items as `effects`(map)
			for(unsigned int i = 0; i < stack_effects.size(); ++i){
				stack_effects[i]->__Drawable_Deattach(this);
			}
			effects_in_list.clear();
			stack_effects.clear();
			has_list_changed = true;
		}

		void Drawable::__Mod_Deattach(Modifier* effect){
			//Called from Mod
			auto it = std::find(stack_effects.begin(), stack_effects.end(), effect);
			if( it != stack_effects.end() ){
				//(*it)->__Drawable_Deattach(this);
				stack_effects.erase(it);
				effects_in_list.erase(effect);
				has_list_changed = true;
			}
		}
	
		void Drawable::Reset(){}
		void Drawable::_Draw(){}
		void Drawable::_DrawEx(){}
		void Drawable::_DrawTransparency(){}
		void Drawable::_DrawTransparencyEx(){}
	}
}