 #include "stdafx.h"
#ifndef RPGLIB_FADEINOUTCANVAS_H
#define RPGLIB_FADEINOUTCANVAS_H

#include "Canvas.h"
namespace Osaka{
	namespace RPGLib{

		class FadeInOutCanvas : public Canvas{
		public:
			FadeInOutCanvas(SDL_Renderer* raw_renderer, Ruler* ruler);
			~FadeInOutCanvas();
			
			void Load(RPGFactory& factory) override;
			void Unload() override;
			void Enter() override;
			void Ready() override;
			void Update() override;
			void Draw() override;

			Component::EventHandler* midAnimation;
			Component::EventHandler* endAnimation;

			/* This is called from Effect EventHandler */
			void OnEffectMidAnimation(Component::EventArgs& e);
			void OnEffectEndAnimation(Component::EventArgs& e);

			/* TODO: Feels like a lot of work...
			 * Called from Script */
			void BeginEndAnimation();

			/* Called from script */
			void SetFadeTimes(float fadein, float fadeout);
		protected:
			/* Owner */
			Square* square;
			/* Owner */
			FadeInFadeOutEffect* effect;
		};
	}
}
#endif