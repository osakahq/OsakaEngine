 #include "stdafx.h"
#ifndef RPGLIB_FADEINOUTSCRIPT_H
#define RPGLIB_FADEINOUTSCRIPT_H

#include "Script.h"
#include "LayerArgs.h"
#include "Callback.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		
		class FadeInOutLayerArgs : public LayerArgs{
		public:
			FadeInOutLayerArgs(){
				removeItselfWhenFinished = true;

				callbackOnMidAnimation = std::make_shared<Component::Callback>();
				callbackOnEndAnimation = std::make_shared<Component::Callback>();

				stillTime = 750;
				fadeInTime = 750;
				fadeOutTime = 750;
			}
			float fadeInTime;
			float stillTime;
			float fadeOutTime;

			/* Ownership of these 2 passes to FadeInOutScript. There is no `_delete` */
			Component::CallbackPTR callbackOnMidAnimation;
			Component::CallbackPTR callbackOnEndAnimation;
			
			/* If true it will remove itself from the stack (layer stack) */
			bool removeItselfWhenFinished;
		};
		
		class FadeInOutScript: public Script{
		public:
			FadeInOutScript(RPGApplication* app, RPGScene* parent, FadeInOutCanvas* canvas);
			~FadeInOutScript();
			
			/* This function is called when entering the stack */
			void Ready(LayerArgs& args) override;
			void Update() override;
			void Exit() override;
			/* This is called from Canvas EventHandler */
			void OnCanvasMidAnimation(Component::EventArgs& e);
			void OnCanvasEndAnimation(Component::EventArgs& e);
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* Owner. Remember you have to set them nullptr in `_delete` */
			Component::CallbackPTR callbackOnMidAnimation;
			Component::CallbackPTR callbackOnEndAnimation;

		private:
			/* NOT Owner */
			FadeInOutCanvas* canvas;
			/* I'm not really sure if I need this but, instead of Starting the end animation right away (in the same Update from Canvas)
			 * With this variable we wait, for the next update (this script Update) */
			bool midAnimationEnded;

			bool removeItselfWhenFinished;
		};
	}
}
#endif