 #include "stdafx.h"

#include "SceneScript.h"
#include "Script.h"
#include "Canvas.h"
#include "UserInterface.h"
#include "Layer.h"

#include "Factory.h"
#include "Ruler.h"
#include "RPGApplication.h"
#include "RPGScene.h"
#include "UserInterface.h"
#include "TextureManager.h"
#include "SceneBuilder.h"

namespace Osaka{
	namespace RPGLib{
		SceneBuilder::SceneBuilder(){
			this->app = NULL;
			this->ruler = NULL;
			this->raw_renderer = NULL;
			this->factory = NULL;
			this->texturem = NULL;
		}
		SceneBuilder::~SceneBuilder(){
			this->app = NULL;
			this->ruler = NULL;
			this->raw_renderer = NULL;
			this->factory = NULL;
			this->texturem = NULL;
		}
		
		void SceneBuilder::Init(RPGApplication* app, Ruler* ruler, SDL_Renderer* raw_renderer, Factory* factory, TextureManager* texturem){
			this->app = app;
			this->ruler = ruler;
			this->raw_renderer = raw_renderer;
			this->factory = factory;
			this->texturem = texturem;

			if( this->app == NULL || this->ruler == NULL || this->raw_renderer == NULL || this->factory == NULL || this->texturem == NULL ){
				throw std::exception("[SceneBuilder] Init failed.");
			}
		}
		RPGScene* SceneBuilder::CreateScene(const char* name){
			//Basically, this is the `Director`
			SceneScript* mainscript = this->CreateMainScript();
			RPGScene* scene = this->CreateRPGScene(name, *mainscript);
			this->CreateLayers(*scene, *mainscript);
			this->MainscriptInit(*mainscript, *scene);
			return scene;
		}

		void SceneBuilder::MainscriptInit(SceneScript& mainscript, RPGScene& scene){
			mainscript.Init(&scene);
		}

		RPGScene* SceneBuilder::CreateRPGScene(const char* name, SceneScript& mainscript){
			RPGScene* scene = new RPGScene(name, &mainscript);
			return scene;
		}

		UserInterface* SceneBuilder::CreateDummyUI(){
			return new UserInterface(raw_renderer, ruler);
		}

		Layer* SceneBuilder::CreateAndInitLayer(const std::string& name, Script& script, Canvas& canvas, UserInterface& ui){
			Layer* layer = new Layer(name, &script, &canvas, &ui);
			//I put Init here because it will be very uncommon to inherit the Layer class
			layer->Init(app);
			return layer;
		}
		
		void SceneBuilder::LayerWrapper(const std::string& layer_id, LayerData& data, RPGScene& scene, SceneScript& mainscript){
			if( layer_id.empty() ){
				throw std::exception("[SceneBuilder] LayerWrapper: layer_id is empty");
			}
			Layer* layer = CreateAndInitLayer(layer_id, *data.script, *data.canvas, *data.ui);
			data.script->Init(layer);
			data.canvas->Init(layer, &scene, data.script, &mainscript);
			data.ui->Init(layer);
			scene.Add(layer);
		}
	}
}