 #include "stdafx.h"

#ifndef RPGLIB_LOADINGSCRIPT_H
#define RPGLIB_LOADINGSCRIPT_H
#include "rpglib_include.h"
#include "Script.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class LoadingScript: public Script{
		public:
			LoadingScript(RPGApplicationPTR& app);
			~LoadingScript();
			void _delete() override;
			
			void Init(RPGLoadingScenePTR& parent, LoadingCanvasPTR& canvas, LoadingUIPTR& ui);
			
			void Ready(Engine::ESceneArgsPTR& params) override;
			void Exit() override;

			void Update() override;

			/* Called when the animation is in total black (and with loading letters) */
			void OnCanvasMidAnimation(Component::EventArgs& e);
			/* Called when the animation went from black to normal */
			void OnCanvasEndAnimation(Component::EventArgs& e);
		private:
			/* NOT Owner. */
			RPGLoadingScenePTR loadingparent;

			/* A temporary variable so I don't have to call parent everytime */
			bool loadCompleted;

			/* This is the id of the scene to switch */
			std::string scene_id;
			/* This is the scene params to send when calling app->Stack/BottomStack */
			Engine::ESceneArgsPTR scene_params;
			TransitionType::Value transition_type;

			/* NOT Owner. Ownership is in RPGLoadingScene */
			LoadingCanvasPTR canvas;
			/* NOT Owner. Ownership is in RPGLoadingScene */
			LoadingUIPTR ui;

			void ResetVariables();
		};
	}
}

#endif
