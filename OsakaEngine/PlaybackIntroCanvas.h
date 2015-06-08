 #include "stdafx.h"

#ifndef RPGLIB_PLAYBACKINTROCANVAS_H
#define RPGLIB_PLAYBACKINTROCANVAS_H
#include "Canvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class PlaybackIntroCanvas : public Canvas{
		public:
			PlaybackIntroCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler, std::string id_engine_logo, std::string id_gamestudio_logo);
			~PlaybackIntroCanvas();
			void _delete();

			void Load(RPGFactoryPTR& factory) override;
			void Unload() override;
			void Update() override;
			void Draw() override;
		private:
			//There are no owners for Drawable objects.
			std::string id_engine_logo; ImagePTR engine_logo; 
			std::string id_gamestudio_logo; ImagePTR gamestudio_logo;
		};
	}
}

#endif