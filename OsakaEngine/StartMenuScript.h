 #include "stdafx.h"
#ifndef RPGLIB_STARTMENUSCRIPT_H
#define RPGLIB_STARTMENUSCRIPT_H

#include "Script.h"
#include "LayerArgs.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		
		class StartMenuScript: public Script{
		public:
			StartMenuScript(RPGApplication* app, RPGScene* parent, StartMenuCanvas* canvas, StartMenuSceneScript* mainscript);
			~StartMenuScript();
			
			void Update(Engine::keyboard_state& state) override;
			/* This function is called when entering the stack */
			void Ready(LayerArgs& args) override;
		/* ----------------------------------------------------------------------------------- */
		protected:
			
		private:
			
			/* NOT Owner. Owner is in parent class (layer). This is a cache reference. */
			StartMenuCanvas* canvas;
			/* NOT Owner. Owner is in RPGScene*/
			StartMenuSceneScript* mainscript;
		};
	}
}
#endif