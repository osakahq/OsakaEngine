 #include "stdafx.h"

#ifndef RPGLIB_PLAYBACKINTROCANVAS_H
#define RPGLIB_PLAYBACKINTROCANVAS_H
#include "Canvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		//Forward
		class FadeInOutLayerArgs;

		class PlaybackIntroCanvas : public Canvas{
		public:
			PlaybackIntroCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler);
			~PlaybackIntroCanvas();
			void _delete();

			void Init(LayerPTR& layer_parent, RPGScenePTR& scene_parent, ScriptPTR& script, SceneScriptPTR& mainscript) override;
			void Load(RPGFactoryPTR& factory) override;
			void Unload() override;
			void Enter() override;
			void Update() override;
			void Draw() override;

			/* These are called from "fadelayer" */
			void CallbackLayerMidAnimation();
			void CallbackLayerEndAnimation();
		private:
			/* phase = 0: just entered 
			 * phase = 1: is fading for engine logo
			 * phase = 2: is showing engine logo 
			 * phase = 3: is fading for gamestudio logo
			 * phase = 4: is ending.
			 * phase = 5: ended. */
			int phase;
			/* This is needed in order to have a correct order, because if phase is incremented after this canvas' update
			 * . it will skip the engine_logo update but will call draw on engine_logo */
			bool movePhaseUp;

			PlaybackIntroSceneScriptPTR mainscript;
			//There are no owners for Drawable objects.
			SquarePTR background;
			ImagePTR engine_logo; 
			ImagePTR gamestudio_logo;

			/* Owner. This is used to time when to switch the images. */
			TimerPTR timer;

			/* This is like a cache. So I don't have to create the object every time */
			std::shared_ptr<FadeInOutLayerArgs> args;
		};
	}
}

#endif