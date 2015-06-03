 #include "stdafx.h"

#ifndef RPGLIB_PLAYBACKINTROCANVAS_H
#define RPGLIB_PLAYBACKINTROCANVAS_H
#include "Canvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class PlaybackIntroCanvas : public Canvas{
		public:
			PlaybackIntroCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler);
			~PlaybackIntroCanvas();
			void _delete();

			void Update() override;
			void Draw() override;
		private:
			
		};
	}
}

#endif