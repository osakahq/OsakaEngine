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
#include "SceneBuilder.h"

namespace Osaka{
	namespace RPGLib{
		SceneBuilder::SceneBuilder(){
			this->app = nullptr;
			this->ruler = nullptr;
			this->raw_renderer = NULL;
			this->factory = nullptr;
		}
		SceneBuilder::~SceneBuilder(){
			this->app = nullptr;
			this->ruler = nullptr;
			this->raw_renderer = NULL;
			this->factory = nullptr;
		}
		
		void SceneBuilder::Init(RPGApplicationPTR& app, RulerPTR& ruler, SDL_Renderer* raw_renderer, FactoryPTR& factory){
			this->app = app;
			this->ruler = ruler;
			this->raw_renderer = raw_renderer;
			this->factory = factory;
		}
		RPGScenePTR SceneBuilder::CreateScene(const char* name){
			//Basically, this is the `Director`
			SceneScriptPTR mainscript = this->CreateMainScript();
			RPGScenePTR scene = this->CreateRPGScene(name, mainscript);
			this->CreateLayers(scene, mainscript);
			this->MainscriptInit(mainscript, scene);
			return scene;
		}

		void SceneBuilder::MainscriptInit(SceneScriptPTR& mainscript, RPGScenePTR& scene){
			mainscript->Init(scene);
		}

		RPGScenePTR SceneBuilder::CreateRPGScene(const char* name, SceneScriptPTR& mainscript){
			RPGScenePTR scene = std::make_shared<RPGScene>(name, mainscript);
			return scene;
		}

		UserInterfacePTR SceneBuilder::CreateDummyUI(){
			return std::make_shared<UserInterface>(raw_renderer, ruler);
		}

		LayerPTR SceneBuilder::CreateAndInitLayer(const char* name, ScriptPTR& script, CanvasPTR& canvas, UserInterfacePTR& ui){
			LayerPTR layer = std::make_shared<Layer>(name, script, canvas, ui);
			layer->Init(app);
			return layer;
		}
		
		void SceneBuilder::LayerWrapper(LayerDataPTR data, RPGScenePTR& scene){
			LayerPTR layer = CreateAndInitLayer(data->layer_id.c_str(), data->script, data->canvas, data->ui);
			data->script->Init(layer);
			data->canvas->Init(layer);
			data->ui->Init(layer);
			scene->Add(layer);
		}
	}
}