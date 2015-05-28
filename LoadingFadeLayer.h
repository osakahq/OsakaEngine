 #include "stdafx.h"
#ifndef RPGLIB_LOADINGFADELAYER_H
#define RPGLIB_LOADINGFADELAYER_H
#include "rpglib_include.h"
#include "Layer.h"
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

		class LoadingFadeLayer: public Layer{
		public:
			LoadingFadeLayer(std::string id, RPGApplicationPTR& app, RPGLoadingScenePTR& parent, LoadingFadeCanvasPTR& canvas, UserInterfacePTR& ui);
			~LoadingFadeLayer();
			void _delete() override;
			void Init();
			/* This function is called directly from RPGLoadingScene */
			void Ready(LayerArgsPTR& args) override;

			/* Called when the animation is in total black (and with loading letters) */
			void OnCanvasMidAnimation(Component::EventArgs& e);
			/* Called when the animation went from black to normal */
			void OnCanvasEndAnimation(Component::EventArgs& e);
		/* ----------------------------------------------------------------------------------- */
		protected:
			void UpdateEx() override;

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

			/* NOT Owner. Owner is in base class. This is a cache reference. `parent` is in base class */
			LoadingFadeCanvasPTR lcanvas;
			/* NOT Owner. This is a cache reference. `parent` is in base class */
			RPGLoadingScenePTR lparent;

			void ResetVariables();
		};
	}
}
#endif