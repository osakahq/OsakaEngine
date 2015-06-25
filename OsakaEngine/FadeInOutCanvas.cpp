 #include "stdafx.h"

#include "Ruler.h"
#include "EventArgs.h"
#include "Registree.h"
#include "EventHandler.h"
#include "FadeInFadeOutEffect.h"
#include "Square.h"
#include "RPGFactory.h"
#include "FadeInOutCanvas.h"

namespace Osaka{
	namespace RPGLib{

		FadeInOutCanvas::FadeInOutCanvas(SDL_Renderer* raw_renderer, Ruler* ruler) 
			: Canvas(raw_renderer, ruler)
		{
			this->square = NULL;
			this->effect = NULL;
			
			midAnimation = new Component::EventHandler();
			endAnimation = new Component::EventHandler();

			//effect->midAnimation/endAnimation Hook events.
		}
		FadeInOutCanvas::~FadeInOutCanvas(){
			delete midAnimation; midAnimation = NULL;
			delete endAnimation; endAnimation = NULL;
			//square, effect are deleted in Unload. Unload will be always be called when quitting.
		}
		void FadeInOutCanvas::Load(RPGFactory& factory){
			Engine::RGBA_HEX hex(0,0,0,0);
			square = factory.CreateSquare(ruler->x_top_left_corner, ruler->y_top_left_corner, ruler->max_height, ruler->max_width);
			square->rgba = hex;
			effect = factory.CreateFadeInFadeOutEffect();
			square->AddMod(effect);

			registree->Register(effect->endAnimation, std::bind(&FadeInOutCanvas::OnEffectEndAnimation, this, std::placeholders::_1));
			registree->Register(effect->midAnimation, std::bind(&FadeInOutCanvas::OnEffectMidAnimation, this, std::placeholders::_1));
		}
		void FadeInOutCanvas::Unload(){
			//This is the owner of effect.
			//When effect is deleted, it automatically Unhooks all the events.
			delete effect; effect = NULL;
			delete square; square = NULL;
		}
		
		void FadeInOutCanvas::OnEffectEndAnimation(Component::EventArgs& e){
			endAnimation->Raise(Component::EventArgs::CreateEmptyArgs());
		}
		void FadeInOutCanvas::OnEffectMidAnimation(Component::EventArgs& e){
			midAnimation->Raise(Component::EventArgs::CreateEmptyArgs());
		}
		void FadeInOutCanvas::BeginEndAnimation(){
			effect->BeginEndAnimation();
		}
		void FadeInOutCanvas::SetFadeTimes(float fadein, float fadeout, float still){
			//This is called when you call the Layer Ready (coming from Script)
			effect->fadeInTime = fadein;
			effect->fadeOutTime = fadeout;
			effect->stillTime = still;
		}
		void FadeInOutCanvas::Ready(){
			LOG("[FadeInOutCanvas] Enter\n");
			effect->Restart();
			square->Reset();
		}
		void FadeInOutCanvas::Enter(){
			
		}
		void FadeInOutCanvas::Update(Engine::keyboard_state& state){
			effect->Update();
			square->Update();
		}
		void FadeInOutCanvas::Draw(){
			square->Draw();
		}
	}
}