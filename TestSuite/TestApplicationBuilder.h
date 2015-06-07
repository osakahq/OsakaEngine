 #include "stdafx.h"
#ifndef TESTSUITE_RPGAPPLICATIONTESTBUILDER_H
#define TESTSUITE_RPGAPPLICATIONTESTBUILDER_H
#include <RPGApplicationBuilder.h>

namespace Osaka{
	namespace TestSuite{

		class TestApplicationBuilder : public RPGLib::RPGApplicationBuilder{
		public:
			
		protected:

			RPGLib::SceneFactoryPTR CreateSceneFactory(RPGLib::FactoryPTR& factory, RPGLib::RPGApplicationPTR& app, RPGLib::TextureManagerPTR& texturem) override;
		};
		
	}
}
#endif