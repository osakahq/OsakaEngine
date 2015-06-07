 #include "stdafx.h"

#ifndef RPGLIB_SCENETESTFACTORY_H
#define RPGLIB_SCENETESTFACTORY_H

#include <SceneFactory.h>

namespace Osaka{
	namespace TestSuite{

		class SceneTestFactory : public RPGLib::SceneFactory {
		public:
			SceneTestFactory(RPGLib::FactoryPTR& factory, RPGLib::RPGApplicationPTR& app, RPGLib::TextureManagerPTR& texturem);
			~SceneTestFactory();
			
			RPGLib::RPGScenePTR CreatePlaybackIntroScene(const char* name) override;
			RPGLib::RPGScenePTR CreateStartMenuScene(const char* name) override;
		};
	}
}

#endif