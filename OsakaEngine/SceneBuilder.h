 #include "stdafx.h"

#ifndef RPGLIB_SCENEBUILDER_H
#define RPGLIB_SCENEBUILDER_H

#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		struct LayerData{
			LayerData(ScriptPTR& s, CanvasPTR& c, UserInterfacePTR& u){
				script = s;
				canvas = c;
				ui = u;
			}
			ScriptPTR script;
			CanvasPTR canvas;
			UserInterfacePTR ui;
		};
		typedef std::shared_ptr<LayerData> LayerDataPTR;

		class SceneBuilder{
		public:
			SceneBuilder();
			virtual ~SceneBuilder();
			//There is no `_delete()` because there is not PTR (See in SceneFactory, it is created then deleted right away)

			virtual void Init(RPGApplicationPTR& app, RulerPTR& ruler, SDL_Renderer* raw_renderer, FactoryPTR& factory, TextureManagerPTR& texturem);

			/* Gives away ownership */
			RPGScenePTR CreateScene(const char* name);
		protected:
			/* In this order. See game-engine.scene-builder.xml diagram for more info. */
			virtual SceneScriptPTR CreateMainScript() = 0;
			virtual RPGScenePTR CreateRPGScene(const char* name, SceneScriptPTR& mainscript);
			virtual void CreateLayers(RPGScenePTR& scene, SceneScriptPTR& mainscript) = 0;

			virtual void MainscriptInit(SceneScriptPTR& mainscript, RPGScenePTR& scene);

			/* Helper functions. Gives away ownership. */
			UserInterfacePTR CreateDummyUI();
			/* This is a helper function that creates and inits the layer */
			LayerPTR CreateAndInitLayer(const char* name, ScriptPTR& script, CanvasPTR& canvas, UserInterfacePTR& ui);
			/* This is a helper function and not required. If you need custom inits, then you have to call the inits in a function like `InitLayer1` */
			void LayerWrapper(std::string layer_id, LayerDataPTR data, RPGScenePTR& scene);
			
			/* NOT owner */
			RPGApplicationPTR app;
			/* NOT owner */
			RulerPTR ruler;
			/* Raw pointer (raw_pointer) */
			SDL_Renderer* raw_renderer;
			/* NOT Owner */
			FactoryPTR factory;
			/* NOT Owner */
			TextureManagerPTR texturem;
		private:

		};
	}
}

#endif