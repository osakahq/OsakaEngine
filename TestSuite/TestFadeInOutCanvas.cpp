 #include "stdafx.h"

#include <Square.h>
#include "_testsuite_macro.h"
#include "TestFadeInOutCanvas.h"

namespace Osaka{
	namespace TestSuite{

		TestFadeInOutCanvas::TestFadeInOutCanvas(SDL_Renderer* raw_renderer, RPGLib::Ruler* ruler) 
			: FadeInOutCanvas(raw_renderer, ruler)
		{
			alpha_255 = false;
		}
		
		void TestFadeInOutCanvas::OnEffectEndAnimation(Component::EventArgs& e){
			if( square->rgba.a == 0 ){
				alpha_0 = true;
			}else{
				alpha_0 = false;
			}
			FadeInOutCanvas::OnEffectEndAnimation(e);
		}
		void TestFadeInOutCanvas::OnEffectMidAnimation(Component::EventArgs& e){
			if( square->rgba.a == 255 ){
				alpha_255 = true;
			}else{
				alpha_255 = false;
			}
			FadeInOutCanvas::OnEffectMidAnimation(e);
		}
		
		void TestFadeInOutCanvas::End(){
			FadeInOutCanvas::End();
			OSAKA_ASSERTEX(TESTID_PHASE1_PLAYBACKINTRO_ALPHA, alpha_255 && alpha_0);
		}
	}
}