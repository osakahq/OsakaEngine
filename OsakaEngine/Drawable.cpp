 #include "stdafx.h"

#include "Effect.h"
#include "Drawable.h"

namespace Osaka{
	namespace RPGLib{
		Drawable::Drawable(SDL_Renderer* raw_renderer){
			this->raw_renderer = raw_renderer;
			info = NULL;
			rgba.r = 255;
			rgba.g = 0;
			rgba.b = 169;
			rgba.a = 255;

			angle = 0.0;
			point.x = 0;
			point.y = 0;
			flip = SDL_FLIP_NONE;
			has_list_changed = true;
		}
		Drawable::~Drawable(){
			raw_renderer = NULL;
			if( info != NULL )
				delete info;

			//I don't need to manually clear the vectors.
		}

		void Drawable::Reset(){
			//This is also called because in a common sense point of view.. when an object is resetted, then its pretty obvious the effects too.
			this->ResetAllEffects();
		}
		void Drawable::Update(){
			if( has_list_changed ){
				temp_list = effects;
			}
			for( auto it = temp_list.begin(); it != temp_list.end(); ++it ){
				(*it)->Update();
			}
		}
		void Drawable::Draw(){

		}

		void Drawable::ResetEffect(std::string id){
			for( auto it = effects.begin(); it != effects.end(); ++it ){
				if( (*it)->id == id ){
					(*it)->Reset();
					return;
				}
			}
		}
		void Drawable::ResetAllEffects(){
			for( auto it = effects.begin(); it != effects.end(); ++it ){
				(*it)->Reset();
			}
		}
		void Drawable::AddEffect(EffectPTR& effect){
			effects.push_back(effect);
			has_list_changed = true;
		}
		
		void Drawable::RemoveEffect(std::string id){
			std::vector<EffectPTR>::iterator it;
			for( it = effects.begin(); it != effects.end(); ++it ){
				if( (*it)->id == id ){
					break;
				}
			}
			effects.erase(it);
			has_list_changed = true;
		}
		void Drawable::RemoveAllEffects(){
			effects.clear();
		}
	}
}