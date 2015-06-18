 #include "stdafx.h"

#include "Effect.h"
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
			RemoveAllEffects();
			raw_renderer = NULL;
			
			//I don't need to manually clear the vectors.
		}

		void Drawable::Reset(){
			//This is also called because in a common sense point of view.. when an object is resetted, then its pretty obvious the effects too.
			this->ResetAllEffects();
		}
		void Drawable::Update(){
			if( has_list_changed ){
				temp_stack_items = stack_effects.size();
				std::copy(stack_effects.begin(), stack_effects.end(), temp_stack);
			}
			for(int i = 0; i < temp_stack_items; ++i){
				temp_stack[i]->Update();
			}
		}
		void Drawable::Draw(){

		}

		void Drawable::ResetAllEffects(){
			//We don't need to copy the stack because the effects dont remove themselves in Reset
			for(unsigned int i = 0; i < stack_effects.size(); ++i){
				stack_effects[i]->Reset();
			}
		}
		void Drawable::AddEffect(Effect* effect){
			if( effects.find(effect->id) != effects.end() ){
				throw std::exception("[Drawable] Effect id already exists.");
			}
			effects[effect->id] = effect;
			stack_effects.push_back(effect);
			/* Raw pointer (raw_pointer) It's okay. When the object is destroyed, it notifies the effect. */
			effect->Attach(this);
			has_list_changed = true;
		}
		
		void Drawable::RemoveEffect(const std::string& id){
			auto it = std::find(stack_effects.begin(), stack_effects.end(), effects[id]);
			(*it)->Deattach();

			stack_effects.erase(it);
			effects.erase(id);
			has_list_changed = true;
		}
		void Drawable::RemoveAllEffects(){
			//vector has the same items as `effects`(map)
			for(unsigned int i = 0; i < stack_effects.size(); ++i){
				stack_effects[i]->Deattach();
			}
			effects.clear();
			stack_effects.clear();
			has_list_changed = true;
		}
	}
}