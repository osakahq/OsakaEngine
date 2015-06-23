 #include "stdafx.h"

#include "Modifier.h"
#include "Drawable.h"

namespace Osaka{
	namespace RPGLib{
		Drawable::Drawable(SDL_Renderer* raw_renderer){
			this->raw_renderer = raw_renderer;
			rgba.r = 255;
			rgba.g = 0;
			rgba.b = 169;
			rgba.a = 255;

			angle = 0.0;
			point.x = 0;
			point.y = 0;
			flip = SDL_FLIP_NONE;
			has_list_changed = true;
			temp_stack_items = 0;
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

		void Drawable::Reset(){}
		void Drawable::Draw(){}
		void Drawable::DrawEx(){}
		void Drawable::DrawBlend(){}

		void Drawable::AddMod(Modifier* effect){
			if( effects_in_list.find(effect) != effects_in_list.end() ){
				throw std::exception("[Drawable] Effect id already exists.");
			}
			effects_in_list[effect] = true;
			stack_effects.push_back(effect);
			/* Raw pointer (raw_pointer) It's okay. When the object is destroyed, it notifies the effect. */
			effect->__Drawable_Attach(this);
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
	}
}