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
			PlaybackIntroScript(RPGApplication* app, RPGScene* parent, PlaybackIntroCanvas* canvas, PlaybackIntroSceneScript* mainscript);
			~PlaybackIntroScript();
			
			void Init(Layer* layer_parent) override;
			void Load(RPGFactory& factory) override;
			void Update(Engine::keyboard_state& state) override;
			/* This function is called when entering the stack */
			void Ready(LayerArgs& args) override;
		/* ----------------------------------------------------------------------------------- */
		protected:
			
		private:
			
			/* NOT Owner. Owner is in parent class (layer). This is a cache reference. */
			PlaybackIntroCanvas* canvas;
			/* NOT Owner. Owner is in RPGScene*/
			PlaybackIntroSceneScript* mainscript;

		};
	}
}
#endif