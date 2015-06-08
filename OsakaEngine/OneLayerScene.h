 #include "stdafx.h"
#ifndef RPGLIB_ONELAYERSCENE_H
#define RPGLIB_ONELAYERSCENE_H
#include "RPGScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/* This is sort of a hack class so we aren't forced to create a SceneScript and the args are handled directed from Script(Layer)
		 * All modifications done to this class (overriden functions) must be considered if they apply also to RPGScene */
		class OneLayerScene : public RPGScene{
		public:
			OneLayerScene(std::string id, SceneScriptPTR& mainscript, OneLayerPTR& onelayer);
			~OneLayerScene();
			void _delete() override;
			
			void Load(RPGFactoryPTR& factory) override;
			void Unload() override;

			void ReadyStandBy(Engine::ESceneArgsPTR& params) override;
			void ReadyShow(Engine::ESceneArgsPTR& params) override;
			void Exit() override;

			void StandBy() override;
			void Focus() override;

			void Update() override;
			void Draw() override;

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* Owner */
			OneLayerPTR onelayer;
		};
	}
}
#endif