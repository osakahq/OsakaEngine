 #include "stdafx.h"

#ifndef RPGLIB_SCENEBUILDER_H
#define RPGLIB_SCENEBUILDER_H

#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		struct LayerData{
			LayerData(Script* s, Canvas* c, UserInterface* u){
				script = s;
				canvas = c;
				ui = u;
			}
			Script* script;
			Canvas* canvas;
			UserInterface* ui;
		};
		
		class SceneBuilder{
		public:
			SceneBuilder();
			virtual ~SceneBuilder();
			//There is no `_delete()` because there is not PTR (See in SceneFactory, it is created then deleted right away)

			virtual void Init(RPGApplication* app, Ruler* ruler, SDL_Renderer* raw_renderer, Factory* factory, TextureManager* texturem);

			/* Gives away ownership */
			RPGScene* CreateScene(const char* name);
		protected:
			/* In this order. See game-engine.scene-builder.xml diagram for more info. */
			virtual SceneScript* CreateMainScript() = 0;
			virtual RPGScene* CreateRPGScene(const char* name, SceneScript& mainscript);
			virtual void CreateLayers(RPGScene& scene, SceneScript& mainscript) = 0;

			virtual void MainscriptInit(SceneScript& mainscript, RPGScene& scene);

			/* Helper functions. Gives away ownership. */
			UserInterface* CreateDummyUI();
			virtual LayerData CreateFadeLayer(RPGScene& scene, PlaybackIntroSceneScript& mainscript);

			/* This is a helper function that creates and inits the layer */
			Layer* CreateAndInitLayer(const std::string& name, Script& script, Canvas& canvas, UserInterface& ui);
			/* This is a helper function and not required. If you need custom inits, then you have to call the inits in a function like `InitLayer1` */
			void LayerWrapper(const std::string& layer_id, LayerData& data, RPGScene& scene, SceneScript& mainscript);
			
			/* NOT owner */
			RPGApplication* app;
			/* NOT owner */
			Ruler* ruler;
			/* Raw pointer (raw_pointer) */
			SDL_Renderer* raw_renderer;
			/* NOT Owner */
			Factory* factory;
			/* NOT Owner */
			TextureManager* texturem;
		private:

		};
	}
}

#endif