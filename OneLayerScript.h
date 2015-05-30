#include "stdafx.h"
#ifndef RPGLIB_ONELAYERSCRIPT_H
#define RPGLIB_ONELAYERSCRIPT_H
#include "Script.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class OneLayerScript : public Script{
		public:
			OneLayerScript(RPGApplicationPTR& app, RPGScenePTR& scene_parent);
			virtual ~OneLayerScript();
			
			virtual void Ready(Engine::ESceneArgsPTR& args) = 0;
			
		/* ----------------------------------------------------------------------------------- */
		protected:
			
		};
	}
}
#endif