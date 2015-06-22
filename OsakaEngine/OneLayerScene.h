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
			OneLayerScene(const std::string& id, SceneScript* mainscript, OneLayer* onelayer);
			~OneLayerScene();
			
			void Load(RPGFactory& factory) override;
			void Unload() override;

			void ReadyStandBy(Engine::ESceneArgs& params) override;
			void ReadyShow(Engine::ESceneArgs& params) override;
			void Exit() override;

			void StandBy() override;
			void Focus() override;

			void Update(Engine::keyboard_state& state) override;
			void Draw() override;

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* Owner */
			OneLayer* onelayer;
		};
	}
}
#endif