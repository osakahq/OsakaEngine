 #include "stdafx.h"

#include <SDLLib.h>
#include <RPGApplication.h>
#include <Factory.h>
#include <LoadingSceneBuilder.h>
#include "PlaybackIntroSceneTestBuilder.h"

#include "SceneTestFactory.h"
namespace Osaka{
	namespace RPGLib{
		SceneTestFactory::SceneTestFactory(FactoryPTR& factory, RPGApplicationPTR& app) : SceneFactory(factory, app){
			
		}
		SceneTestFactory::~SceneTestFactory(){

		}
		
		RPGScenePTR SceneTestFactory::CreatePlaybackIntroScene(const char* name){
			PlaybackIntroSceneTestBuilder* builder = new PlaybackIntroSceneTestBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory);
			RPGScenePTR scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}

	}
}