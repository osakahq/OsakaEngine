 #include "stdafx.h"

#ifndef RPGLIB_LOADINGCANVAS_H
#define RPGLIB_LOADINGCANVAS_H
#include "engine_include.h"
#include "rpglib_include.h"
#include "Canvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class LoadingCanvas : public Canvas{
		public:
			LoadingCanvas(RPGApplicationPTR& app);
			~LoadingCanvas();
			void _delete();

			void Init(TimerPTR& timer);
			void Load();
			void Unload();
			void Show();
			void Hide();
			void StandBy();
			void Focus();
			void Update();
			void Draw();

			void Reset();

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

			/* Color of the box. The only value changing, is the alpha */
			Engine::RGBA_HEX color;

			/* Timer for the animation */
			TimerPTR timer;

			/* The box that covers the entire screen */
			SDL_Rect carp;
		};
	}
}

#endif