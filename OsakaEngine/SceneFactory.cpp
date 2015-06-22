 #include "stdafx.h"

#include "EScene.h"
#include "DummyScene.h"

#include "SceneScript.h"
#include "SDLLib.h"
#include "RPGApplication.h"
#include "Factory.h"
#include "LoadingSceneBuilder.h"
#include "PlaybackIntroSceneBuilder.h"
#include "StartMenuSceneBuilder.h"
#include "TextureManager.h"
#include "SceneFactory.h"
namespace Osaka{
	namespace RPGLib{
		SceneFactory::SceneFactory(Factory* factory, RPGApplication* app, TextureManager* texturem){
			this->factory = factory;
			this->app = app;
			this->texturem = texturem;

			if( this->factory == NULL || this->app == NULL || this->texturem == NULL ){
				throw std::exception("[SceneFactory] Failed nullptr check.");
			}
		}
		SceneFactory::~SceneFactory(){
			factory = NULL;
			app = NULL;
			texturem = NULL;
		}
		
		RPGScene* SceneFactory::CreateLoadingScene(const char* name){
			LoadingSceneBuilder* builder = new LoadingSceneBuilder(factory->assetm);
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory, texturem);
			RPGScene* scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
		RPGScene* SceneFactory::CreatePlaybackIntroScene(const char* name){
			PlaybackIntroSceneBuilder* builder = new PlaybackIntroSceneBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory, texturem);
			RPGScene* scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
		RPGScene* SceneFactory::CreateStartMenuScene(const char* name){
			StartMenuSceneBuilder* builder = new StartMenuSceneBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory, texturem);
			RPGScene* scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}

		DummyScene* SceneFactory::CreateDummyScene(const char* name){
			SceneScript* mainscript = new SceneScript(app);
			DummyScene* scene = new DummyScene(name, mainscript);
			/* Not really needed, but just in case. */
			mainscript->Init(scene);
			return scene;
		}
	}
}