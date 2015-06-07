 #include "stdafx.h"

#include <TextureManager.h>
#include <SDLLib.h>
#include <RPGApplication.h>
#include <Factory.h>
#include <LoadingSceneBuilder.h>
#include "StartMenuSceneTestBuilder.h"
#include "PlaybackIntroSceneTestBuilder.h"

#include "SceneTestFactory.h"
namespace Osaka{
	namespace TestSuite{
		SceneTestFactory::SceneTestFactory(RPGLib::FactoryPTR& factory, RPGLib::RPGApplicationPTR& app, RPGLib::TextureManagerPTR& texturem) : SceneFactory(factory, app, texturem){
			
		}
		SceneTestFactory::~SceneTestFactory(){

		}
		
		RPGLib::RPGScenePTR SceneTestFactory::CreatePlaybackIntroScene(const char* name){
			PlaybackIntroSceneTestBuilder* builder = new PlaybackIntroSceneTestBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory, texturem);
			RPGLib::RPGScenePTR scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
		RPGLib::RPGScenePTR SceneTestFactory::CreateStartMenuScene(const char* name){
			StartMenuSceneTestBuilder* builder = new StartMenuSceneTestBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory, texturem);
			RPGLib::RPGScenePTR scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
	}
}