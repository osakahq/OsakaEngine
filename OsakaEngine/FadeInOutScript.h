 #include "stdafx.h"
#ifndef RPGLIB_FADEINOUTSCRIPT_H
#define RPGLIB_FADEINOUTSCRIPT_H

#include "Script.h"
#include "LayerArgs.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		
		class FadeInOutLayerArgs : public LayerArgs{
		public:
			//float fadeInTime;
			//float fadeOutTime;

			std::function<void()> callbackOnMidAnimation;
			std::function<void()> callbackOnEndAnimation;
		};
		typedef std::shared_ptr<FadeInOutLayerArgs> FadeInOutLayerArgsPTR;

		class FadeInOutScript: public Script{
		public:
			FadeInOutScript(RPGApplicationPTR& app, RPGScenePTR& parent, FadeInOutCanvasPTR& canvas);
			~FadeInOutScript();
			void _delete() override;
			
			/* This function is called when entering the stack */
			void Ready(LayerArgsPTR& args) override;
			void Update() override;
			void Exit() override;
			/* This is called from Canvas EventHandler */
			void OnCanvasMidAnimation(Component::EventArgs& e);
			void OnCanvasEndAnimation(Component::EventArgs& e);
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* Remember you have to set them nullptr in `_delete` */
			std::function<void()> callbackOnMidAnimation;
			std::function<void()> callbackOnEndAnimation;

		private:
			/* NOT Owner */
			FadeInOutCanvasPTR canvas;
			/* I'm not really sure if I need this but, instead of Starting the end animation right away (in the same Update from Canvas)
			 * With this variable we wait, for the next update (this script Update) */
			bool midAnimationEnded;
		};
	}
}
#endif