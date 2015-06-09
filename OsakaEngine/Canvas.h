 #include "stdafx.h"
#ifndef RPGLIB_CANVAS_H
#define RPGLIB_CANVAS_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{

		class Canvas{
		public:
			Canvas(SDL_Renderer* raw_renderer, RulerPTR& ruler);
			virtual ~Canvas();
			virtual void _delete();
			/* I decided that it just easier to let Canvas have these references. Canvas shouldn't have responsability other than its objective.
			 * This `Init` function is optional. Base function will only set layer_parent and scene_parent. It will do nothing for script and mainscript, thats up to the
			 * . derived class to override and std::dynamic_cast them.
			 * script = script brother. mainscript = scene script (parent script) */
			virtual void Init(LayerPTR& layer_parent, RPGScenePTR& scene_parent, ScriptPTR& script, SceneScriptPTR& mainscript);
			/* This is so that in the derived class doesn't have to call Init(layer, scene, script, mainscript) */
			virtual void Init(LayerPTR& layer_parent, RPGScenePTR& scene_parent);

			virtual void Load(RPGFactoryPTR& factory);
			virtual void Unload();

			virtual void Enter();
			virtual void Ready();
			virtual void Exit();

			virtual void Show();
			virtual void StandBy();
			virtual void Focus();

			virtual void Update() = 0;
			virtual void Draw() = 0;

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner. Raw */
			SDL_Renderer* raw_renderer;
			/* NOT Owner. Layer parent. */
			LayerPTR layer_parent;
			/* NOT Owner. Scene parent. */
			RPGScenePTR scene_parent;
			/* NOT Owner */
			RulerPTR ruler;
		};
	}
}
#endif