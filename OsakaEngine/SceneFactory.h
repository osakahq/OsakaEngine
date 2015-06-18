 #include "stdafx.h"

#ifndef RPGLIB_SCENEFACTORY_H
#define RPGLIB_SCENEFACTORY_H

#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class SceneFactory {
		public:
			SceneFactory(Factory* factory, RPGApplication* app, TextureManager* texturem);
			virtual ~SceneFactory();
			
			virtual RPGScene* CreateLoadingScene(const char* name);
			virtual RPGScene* CreatePlaybackIntroScene(const char* name);

			virtual RPGScene* CreateStartMenuScene(const char* name);
			
			virtual DummyScene* CreateDummyScene(const char* name);
		protected:
			/* NOT Owner */
			Factory* factory;
			/* NOT Owner */
			RPGApplication* app;
			/* NOT Owner */
			TextureManager* texturem;
		};
	}
}

#endif