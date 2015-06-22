 #include "stdafx.h"
#ifndef TESTSUITE_TESTFADEINOUTCANVAS_H
#define TESTSUITE_TESTFADEINOUTCANVAS_H

#include <FadeInOutCanvas.h>
namespace Osaka{
	namespace TestSuite{

		class TestFadeInOutCanvas : public RPGLib::FadeInOutCanvas{
		public:
			TestFadeInOutCanvas(SDL_Renderer* raw_renderer, RPGLib::Ruler* ruler);
			
			void End() override;
			
			void OnEffectMidAnimation(Component::EventArgs& e) override;
			void OnEffectEndAnimation(Component::EventArgs& e) override;
		protected:
		private:
			bool alpha_255;
			bool alpha_0;
		};
	}
}
#endif