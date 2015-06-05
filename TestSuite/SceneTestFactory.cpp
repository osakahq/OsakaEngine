 #include "stdafx.h"

#include <SDLLib.h>
#include <RPGApplication.h>
#include <Factory.h>
#include <LoadingSceneBuilder.h>
#include "StartMenuSceneTestBuilder.h"
#include "PlaybackIntroSceneTestBuilder.h"

#include "SceneTestFactory.h"
namespace Osaka{
	namespace TestSuite{
		SceneTestFactory::SceneTestFactory(RPGLib::FactoryPTR& factory, RPGLib::RPGApplicationPTR& app) : SceneFactory(factory, app){
			
		}
		SceneTestFactory::~SceneTestFactory(){

		}
		
		RPGLib::RPGScenePTR SceneTestFactory::CreatePlaybackIntroScene(const char* name){
			PlaybackIntroSceneTestBuilder* builder = new PlaybackIntroSceneTestBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory);
			RPGLib::RPGScenePTR scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
		RPGLib::RPGScenePTR SceneTestFactory::CreateStartMenuScene(const char* name){
			StartMenuSceneTestBuilder* builder = new StartMenuSceneTestBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory);
			RPGLib::RPGScenePTR scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
	}
}