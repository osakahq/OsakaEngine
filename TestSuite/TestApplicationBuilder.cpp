 #include "stdafx.h"

#include "SceneTestFactory.h"
#include "TestApplicationBuilder.h"

namespace Osaka{
	namespace TestSuite{
		
		RPGLib::SceneFactoryPTR TestApplicationBuilder::CreateSceneFactory(RPGLib::FactoryPTR& factory, RPGLib::RPGApplicationPTR& app){
			return std::make_shared<SceneTestFactory>(factory, app);
		}

	}
}