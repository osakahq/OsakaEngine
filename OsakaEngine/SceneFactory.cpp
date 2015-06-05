 #include "stdafx.h"

#include "EScene.h"
#include "DummyScene.h"

#include "SDLLib.h"
#include "RPGApplication.h"
#include "Factory.h"
#include "LoadingSceneBuilder.h"
#include "PlaybackIntroSceneBuilder.h"
#include "StartMenuSceneBuilder.h"

#include "SceneFactory.h"
namespace Osaka{
	namespace RPGLib{
		SceneFactory::SceneFactory(FactoryPTR& factory, RPGApplicationPTR& app){
			this->factory = factory;
			this->app = app;
		}
		SceneFactory::~SceneFactory(){
#ifdef _DEBUG
			_CHECKDELETE("SceneFactory");
#endif	
		}
		void SceneFactory::_delete(){
			factory = nullptr;
			app = nullptr;
		}

		RPGScenePTR SceneFactory::CreateLoadingScene(const char* name){
			LoadingSceneBuilder* builder = new LoadingSceneBuilder(factory->assetm);
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory);
			RPGScenePTR scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
		RPGScenePTR SceneFactory::CreatePlaybackIntroScene(const char* name){
			PlaybackIntroSceneBuilder* builder = new PlaybackIntroSceneBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory);
			RPGScenePTR scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
		RPGScenePTR SceneFactory::CreateStartMenuScene(const char* name){
			StartMenuSceneBuilder* builder = new StartMenuSceneBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory);
			RPGScenePTR scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}

		std::shared_ptr<DummyScene> SceneFactory::CreateDummyScene(const char* name){
			DummyScenePTR scene = std::make_shared<DummyScene>(name);
			return scene;
		}
	}
}