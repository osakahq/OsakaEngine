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
			StartMenuScript(RPGApplicationPTR& app, RPGScenePTR& parent, StartMenuCanvasPTR& canvas, StartMenuSceneScriptPTR& mainscript);
			~StartMenuScript();
			void _delete() override;
			
			void Update() override;
			/* This function is called when entering the stack */
			void Ready(LayerArgsPTR& args) override;
		/* ----------------------------------------------------------------------------------- */
		protected:
			
		private:
			
			/* NOT Owner. Owner is in parent class (layer). This is a cache reference. */
			StartMenuCanvasPTR canvas;
			/* NOT Owner. Owner is in RPGScene*/
			StartMenuSceneScriptPTR mainscript;
		};
	}
}
#endif