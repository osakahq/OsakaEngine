 #include "stdafx.h"

#ifndef RPGLIB_PLAYBACKINTROSCRIPT_H
#define RPGLIB_PLAYBACKINTROSCRIPT_H
#include "rpglib_include.h"
#include "Script.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class PlaybackIntroScript: public Script{
		public:
			PlaybackIntroScript(RPGApplicationPTR& app);
			~PlaybackIntroScript();
			void _delete();
			
			void Init(PlaybackIntroCanvasPTR& canvas, PlaybackIntroUIPTR& ui);
			void Load();
			void Unload();
			void Show(Engine::EScenePassParamsPTR& params);
			void Hide();
			void StandBy();
			void StandBy(Engine::EScenePassParamsPTR& params);
			void Focus();
			void Update();
			void Draw();

			/* Called by RPGApplication (exitgame,loadgame) */
			void Reset();

		private:
			/* NOT Owner. Ownership is in RPGScene */
			PlaybackIntroCanvasPTR canvas;
			/* NOT Owner. Ownership is in RPGScene */
			PlaybackIntroUIPTR ui;
		};
	}
}

#endif
