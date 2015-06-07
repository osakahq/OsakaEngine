 #include "stdafx.h"

#include "Ruler.h"
#include "EventArgs.h"
#include "EventHandler.h"
#include "FadeInFadeOutEffect.h"
#include "Square.h"
#include "FadeInOutCanvas.h"

#define FADEINOUTCANVAS_MIDANIMATION 428046
#define FADEINOUTCANVAS_ENDANIMATION 654887

namespace Osaka{
	namespace RPGLib{

		FadeInOutCanvas::FadeInOutCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler, SquarePTR& square, FadeInFadeOutEffectPTR& effect) : Canvas(raw_renderer, ruler){
			Engine::RGBA_HEX hex(0,0,0,0);
			square->rgba = hex;
			this->square = square;
			this->effect = effect;
			
			square->AddEffect(std::static_pointer_cast<Effect>(effect));
			square->square.x = ruler->x_top_left_corner;
			square->square.y = ruler->y_top_left_corner;
			square->square.h = ruler->max_height;
			square->square.w = ruler->max_width;

			midAnimation = std::make_shared<Component::EventHandler>();
			endAnimation = std::make_shared<Component::EventHandler>();

			effect->endAnimation->Hook(FADEINOUTCANVAS_MIDANIMATION, std::bind(&FadeInOutCanvas::OnEffectEndAnimation, this, std::placeholders::_1));
			effect->midAnimation->Hook(FADEINOUTCANVAS_ENDANIMATION, std::bind(&FadeInOutCanvas::OnEffectMidAnimation, this, std::placeholders::_1));
			//effect->midAnimation/endAnimation Hook events.
		}
		FadeInOutCanvas::~FadeInOutCanvas(){
			//No need to `square = nullptr` or `effect = nullptr`
			//No need for nullptr on the eventhandlers
		}
		void FadeInOutCanvas::_delete(){
			Canvas::_delete();
			effect->endAnimation->Unhook(FADEINOUTCANVAS_MIDANIMATION);
			effect->midAnimation->Unhook(FADEINOUTCANVAS_ENDANIMATION);
		}
		void FadeInOutCanvas::OnEffectEndAnimation(Component::EventArgs& e){
			endAnimation->Raise(Component::EmptyEventArgs);
		}
		void FadeInOutCanvas::OnEffectMidAnimation(Component::EventArgs& e){
			midAnimation->Raise(Component::EmptyEventArgs);
		}
		void FadeInOutCanvas::BeginEndAnimation(){
			effect->BeginEndAnimation();
		}
		void FadeInOutCanvas::Ready(){
			
		}
		void FadeInOutCanvas::Enter(){
			square->Reset();
		}
		void FadeInOutCanvas::Update(){
			square->Update();
		}
		void FadeInOutCanvas::Draw(){
			square->Draw();
		}
	}
}