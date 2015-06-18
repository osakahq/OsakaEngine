 #include "stdafx.h"
#ifndef TESTSUITE_RPGAPPLICATIONTESTBUILDER_H
#define TESTSUITE_RPGAPPLICATIONTESTBUILDER_H
#include <RPGApplicationBuilder.h>

namespace Osaka{
	namespace TestSuite{

		class TestApplicationBuilder : public RPGLib::RPGApplicationBuilder{
		public:
			
		protected:

			RPGLib::SceneFactory* CreateSceneFactory(RPGLib::Factory& factory, RPGLib::RPGApplication& app, RPGLib::TextureManager& texturem) override;
		};
		
	}
}
#endif