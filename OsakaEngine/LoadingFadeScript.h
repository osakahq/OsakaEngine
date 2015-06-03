 #include "stdafx.h"
#ifndef RPGLIB_LOADINGFADESCRIPT_H
#define RPGLIB_LOADINGFADESCRIPT_H
#include "rpglib_include.h"
#include "Script.h"
#include "LayerArgs.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class LoadingFadeLayerArgs : public LayerArgs{
		public:
			std::string scene_id;
			TransitionType::Value type;
			Engine::ESceneArgsPTR scene_params;
		};
		typedef std::shared_ptr<LoadingFadeLayerArgs> LoadingFadeLayerArgsPTR;

		/* ----------------------------------------------------------------------------------- */
		class LoadingFadeScript: public Script{
		public:
			LoadingFadeScript(RPGApplicationPTR& app, RPGScenePTR& parent, LoadingFadeCanvasPTR& canvas, LoadingSceneScriptPTR& mainscript);
			~LoadingFadeScript();
			void _delete() override;
			void Init(LayerPTR& layer_parent) override;
			
			void Update() override;
			/* This function is called when entering the stack */
			void Ready(LayerArgsPTR& args) override;

			/* Called when the animation is in total black (and with loading letters) */
			void OnCanvasMidAnimation(Component::EventArgs& e);
			/* Called when the animation went from black to normal */
			void OnCanvasEndAnimation(Component::EventArgs& e);
		/* ----------------------------------------------------------------------------------- */
		protected:
			
		private:
			/* A temporary variable so I don't have to call parent everytime */
			bool loadCompleted;

			/* To know when to start the canvas animation inside the update */
			bool startAnimation;

			/* This is the id of the scene to switch */
			std::string scene_id;
			/* This is the scene params to send when calling app->Stack/BottomStack */
			Engine::ESceneArgsPTR scene_params;
			TransitionType::Value transition_type;

			/* NOT Owner. Owner is in parent class (Layer). This is a cache reference. */
			LoadingFadeCanvasPTR lcanvas;
			/* NOT Owner. Owner is in RPGScene*/
			LoadingSceneScriptPTR mainscript;

			void ResetVariables();
		};
	}
}
#endif