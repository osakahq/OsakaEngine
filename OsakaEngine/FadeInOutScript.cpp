 #include "stdafx.h"

#include "EventHandler.h"
#include "EventArgs.h"
#include "FadeInOutCanvas.h"
#include "FadeInOutScript.h"

#define FADEINOUTSCRIPT_MIDANIMATION 532763
#define FADEINOUTSCRIPT_ENDANIMATION 468145

namespace Osaka{
	namespace RPGLib{
		FadeInOutScript::FadeInOutScript(RPGApplicationPTR& app, RPGScenePTR& parent, FadeInOutCanvasPTR& canvas) : Script(app, parent){
			this->canvas = canvas;
			canvas->endAnimation->Hook(FADEINOUTSCRIPT_ENDANIMATION, std::bind(&FadeInOutScript::OnCanvasEndAnimation, this, std::placeholders::_1));
			canvas->midAnimation->Hook(FADEINOUTSCRIPT_MIDANIMATION, std::bind(&FadeInOutScript::OnCanvasMidAnimation, this, std::placeholders::_1));
		}
		FadeInOutScript::~FadeInOutScript(){

		}
		void FadeInOutScript::_delete(){
			canvas->endAnimation->Unhook(FADEINOUTSCRIPT_ENDANIMATION);
			canvas->midAnimation->Unhook(FADEINOUTSCRIPT_MIDANIMATION);

			callbackOnMidAnimation = nullptr;
			callbackOnEndAnimation = nullptr;
			canvas = nullptr;
			Script::_delete();
		}
			
		/* This function is called when entering the stack */
		void FadeInOutScript::Ready(LayerArgsPTR& args){
			midAnimationEnded = false;
			FadeInOutLayerArgsPTR fargs = std::dynamic_pointer_cast<FadeInOutLayerArgs>(args);
			callbackOnEndAnimation = fargs->callbackOnEndAnimation;
			callbackOnMidAnimation = fargs->callbackOnMidAnimation;
		}

		void FadeInOutScript::OnCanvasMidAnimation(Component::EventArgs& e){
			midAnimationEnded = true;
			if( callbackOnEndAnimation != nullptr )
				callbackOnEndAnimation();
		}
		void FadeInOutScript::OnCanvasEndAnimation(Component::EventArgs& e){
			if( callbackOnMidAnimation != nullptr )
				callbackOnMidAnimation();
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