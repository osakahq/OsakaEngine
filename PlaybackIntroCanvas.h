 #include "stdafx.h"

#ifndef RPGLIB_PLAYBACKINTROCANVAS_H
#define RPGLIB_PLAYBACKINTROCANVAS_H
#include "engine_include.h"
#include "rpglib_include.h"
#include "Canvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class PlaybackIntroCanvas : public Canvas{
		public:
			PlaybackIntroCanvas(RPGApplicationPTR& app);
			~PlaybackIntroCanvas();
			void _delete();

			void Init();
			void Load();
			void Unload();
			void Show();
			void Hide();
			void StandBy();
			void Focus();
			void Update();
			void Draw();

			void Reset();
		private:
			
		};
	}
}

#endif