 #include "stdafx.h"

#include "SceneTestFactory.h"
#include "TestApplicationBuilder.h"

namespace Osaka{
	namespace TestSuite{
		
		RPGLib::SceneFactory* TestApplicationBuilder::CreateSceneFactory(RPGLib::Factory& factory, RPGLib::RPGApplication& app, RPGLib::TextureManager& texturem){
			return new SceneTestFactory(&factory, &app, &texturem);
		}

	}
}