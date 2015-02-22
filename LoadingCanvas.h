 #include "stdafx.h"

#ifndef RPGLIB_LOADINGCANVAS_H
#define RPGLIB_LOADINGCANVAS_H
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

			bool isAnimating;
			/* When the animation starts, it has to stop in black (and letters "loading"), we need script to let us know when to being the end animation */
			bool beginSecondPart;


			/* Transparency of the box */
			Uint8 alpha;

			/* Timer for the animation */
			TimerPTR timer;
		};
	}
}

#endif