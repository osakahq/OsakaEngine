 #include "stdafx.h"
#ifndef RPGLIB_PLAYBACKINTROSCRIPT_H
#define RPGLIB_PLAYBACKINTROSCRIPT_H

#include "Script.h"
#include "LayerArgs.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class PlaybackIntroScript: public Script{
		public:
			PlaybackIntroScript(RPGApplicationPTR& app, RPGScenePTR& parent, PlaybackIntroCanvasPTR& canvas, PlaybackIntroSceneScriptPTR& mainscript);
			~PlaybackIntroScript();
			void _delete() override;
			void Init(LayerPTR& layer_parent) override;
			void Load() override;
			void Update() override;
			/* This function is called when entering the stack */
			void Ready(LayerArgsPTR& args) override;
		/* ----------------------------------------------------------------------------------- */
		protected:
			
		private:
			
			/* NOT Owner. Owner is in parent class (layer). This is a cache reference. */
			PlaybackIntroCanvasPTR canvas;
			/* NOT Owner. Owner is in RPGScene*/
			PlaybackIntroSceneScriptPTR mainscript;

		};
	}
}
#endif