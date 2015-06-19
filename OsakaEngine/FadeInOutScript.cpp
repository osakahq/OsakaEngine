 #include "stdafx.h"

#include "Layer.h"
#include "RPGScene.h"
#include "EventHandler.h"
#include "EventArgs.h"
#include "Registree.h"
#include "FadeInOutCanvas.h"
#include "FadeInOutScript.h"

#define FADEINOUTSCRIPT_MIDANIMATION 532763
#define FADEINOUTSCRIPT_ENDANIMATION 468145

namespace Osaka{
	namespace RPGLib{
		FadeInOutScript::FadeInOutScript(RPGApplication* app, RPGScene* parent, FadeInOutCanvas* canvas) 
			: Script(app, parent)
		{
			this->canvas = canvas;

			registree->Register(canvas->endAnimation, std::bind(&FadeInOutScript::OnCanvasEndAnimation, this, std::placeholders::_1));
			registree->Register(canvas->midAnimation, std::bind(&FadeInOutScript::OnCanvasMidAnimation, this, std::placeholders::_1));
		}
		FadeInOutScript::~FadeInOutScript(){
			canvas = NULL;
		}
			
		/* This function is called when entering the stack */
		void FadeInOutScript::Ready(LayerArgs& args){
			midAnimationEnded = false;
			FadeInOutLayerArgs* fargs = dynamic_cast<FadeInOutLayerArgs*>(&args);
			callbackOnEndAnimation = fargs->callbackOnEndAnimation;
			callbackOnMidAnimation = fargs->callbackOnMidAnimation;
			canvas->SetFadeTimes(fargs->fadeInTime, fargs->fadeOutTime);
			removeItselfWhenFinished = fargs->removeItselfWhenFinished;
		}

		void FadeInOutScript::OnCanvasMidAnimation(Component::EventArgs& e){
			midAnimationEnded = true;
			if( callbackOnMidAnimation != nullptr )
				callbackOnMidAnimation->Call(e);
		}
		void FadeInOutScript::OnCanvasEndAnimation(Component::EventArgs& e){
			if( callbackOnEndAnimation != nullptr )
				callbackOnEndAnimation->Call(e);

			if( removeItselfWhenFinished ){
				//Safe to remove, because this event fires up inside Update
				scene_parent->Remove(this->layer_parent->id);
				callbackOnMidAnimation = nullptr;
				callbackOnEndAnimation = nullptr;
			}
		}
		void FadeInOutScript::Update(){
			if( midAnimationEnded ){
				canvas->BeginEndAnimation();
				midAnimationEnded = false;
			}
		}
		void FadeInOutScript::Exit(){
			callbackOnMidAnimation = nullptr;
			callbackOnEndAnimation = nullptr;
			midAnimationEnded = false;
		}
	}
}