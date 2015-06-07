 #include "stdafx.h"

#ifndef RPGLIB_SCENEFACTORY_H
#define RPGLIB_SCENEFACTORY_H

#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		class SceneFactory {
		public:
			SceneFactory(FactoryPTR& factory, RPGApplicationPTR& app, TextureManagerPTR& texturem);
			virtual ~SceneFactory();
			virtual void _delete();

			virtual RPGScenePTR CreateLoadingScene(const char* name);
			virtual RPGScenePTR CreatePlaybackIntroScene(const char* name);

			virtual RPGScenePTR CreateStartMenuScene(const char* name);
			
			virtual DummyScenePTR CreateDummyScene(const char* name);
		protected:
			/* NOT Owner */
			FactoryPTR factory;
			/* NOT Owner */
			RPGApplicationPTR app;
			/* NOT Owner */
			TextureManagerPTR texturem;
		};
	}
}

#endif