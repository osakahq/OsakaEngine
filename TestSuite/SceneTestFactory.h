 #include "stdafx.h"

#ifndef RPGLIB_SCENETESTFACTORY_H
#define RPGLIB_SCENETESTFACTORY_H

#include <SceneFactory.h>

namespace Osaka{
	namespace TestSuite{

		class SceneTestFactory : public RPGLib::SceneFactory {
		public:
			SceneTestFactory(RPGLib::Factory* factory, RPGLib::RPGApplication* app, RPGLib::TextureManager* texturem);
			~SceneTestFactory();
			
			RPGLib::RPGScene* CreatePlaybackIntroScene(const char* name) override;
			RPGLib::RPGScene* CreateStartMenuScene(const char* name) override;
		};
	}
}

#endif