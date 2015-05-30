 #include "stdafx.h"
#ifndef RPGLIB_ONELAYER_H
#define RPGLIB_ONELAYER_H
#include "Layer.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class OneLayer : public Layer{
		public:
			OneLayer(std::string id, OneLayerScriptPTR& script, CanvasPTR& canvas, UserInterfacePTR& ui);
			~OneLayer();
			void _delete() override;

			/* When entering the stack(vector) in RPGScene. Completely overriden: Doesn't call parent:Ready function */
			void Ready(Engine::ESceneArgsPTR& args);
			
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner. Owner is in base class. */
			OneLayerScriptPTR onelayerscript;
		};
	}
}
#endif