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
			void _delete() override;
			
			void Update() override;
			void Draw() override;
		private:
		};
	}
}

#endif