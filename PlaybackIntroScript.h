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
			void _delete() override;
			
			void Init(RPGScenePTR& parent, PlaybackIntroCanvasPTR& canvas, PlaybackIntroUIPTR& ui);
			void Ready(Engine::ESceneArgsPTR& params) override;
			void Update() override;
			void Focus() override;
			
		private:
			/* NOT Owner. Ownership is in RPGScene */
			PlaybackIntroCanvasPTR canvas;
			/* NOT Owner. Ownership is in RPGScene */
			PlaybackIntroUIPTR ui;
		};
	}
}

#endif
