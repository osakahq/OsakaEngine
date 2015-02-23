 #include "stdafx.h"

#ifndef RPGLIB_PLAYBACKINTROUI_H
#define RPGLIB_PLAYBACKINTROUI_H
#include "UserInterface.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class PlaybackIntroUI : public UserInterface{
		public:
			PlaybackIntroUI(RPGApplicationPTR& app);
			~PlaybackIntroUI();
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