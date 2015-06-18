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
		SceneTestFactory::SceneTestFactory(RPGLib::Factory* factory, RPGLib::RPGApplication* app, RPGLib::TextureManager* texturem) : SceneFactory(factory, app, texturem){
			
		}
		SceneTestFactory::~SceneTestFactory(){

		}
		
		RPGLib::RPGScene* SceneTestFactory::CreatePlaybackIntroScene(const char* name){
			PlaybackIntroSceneTestBuilder* builder = new PlaybackIntroSceneTestBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory, texturem);
			RPGLib::RPGScene* scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
		RPGLib::RPGScene* SceneTestFactory::CreateStartMenuScene(const char* name){
			StartMenuSceneTestBuilder* builder = new StartMenuSceneTestBuilder();
			builder->Init(app, app->ruler, app->sdl->GetRAWSDLRenderer(), factory, texturem);
			RPGLib::RPGScene* scene = builder->CreateScene(name);
			delete builder;
			return scene;
		}
	}
}