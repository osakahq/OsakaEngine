 #include "stdafx.h"

#ifndef RPGLIB_LOADINGFADECANVAS_H
#define RPGLIB_LOADINGFADECANVAS_H
#include "engine_include.h"
#include "rpglib_include.h"
#include "Canvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class LoadingFadeCanvas : public Canvas{
		public:
			LoadingFadeCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler, TimerPTR& timer);
			~LoadingFadeCanvas();
			void _delete() override;

			void Update() override;
			void Draw() override;

			void StartAnimation(TransitionType::Value type);
			void BeginEndAnimation();

			/* Owner. Mid animation is when the animation is in total back */
			Component::EventHandlerPTR midAnimation;
			/* Owner. End animation is when the animation is done and scene is ready to take itself out */
			Component::EventHandlerPTR endAnimation;
		private:
			/* Switch or stack animation? */
			TransitionType::Value type;

			/* From Script */
			bool isAnimating;
			/* From Script. When the animation starts, it has to stop in black (and letters "loading"), we need script to let us know when to being the end animation */
			bool beginSecondPart;

			/* So we can know we finished, the first animation */
			bool onMidAnimation;

			/* This is used when we no longer need to update but only draw (fade out animation ended) */
			bool skipUpdate;

			/* Color of the box. The only value changing, is the alpha */
			Engine::RGBA_HEX color;

			/* Owner. Timer for the animation */
			TimerPTR timer;

			/* The box that covers the entire screen */
			SDL_Rect carp;
		};
	}
}

#endif