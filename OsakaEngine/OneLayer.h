 #include "stdafx.h"
#ifndef RPGLIB_ONELAYER_H
#define RPGLIB_ONELAYER_H
#include "Layer.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class OneLayer : public Layer{
		public:
			OneLayer(const std::string& id, OneLayerScript* script, Canvas* canvas, UserInterface* ui);
			~OneLayer();
			
			/* When entering the stack(vector) in RPGScene. Completely overriden: Doesn't call parent:Ready function */
			void Ready(Engine::ESceneArgs& args);
			
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner. Owner is in base class. */
			OneLayerScript* onelayerscript;
		};
	}
}
#endif