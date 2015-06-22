 #include "stdafx.h"
#ifndef RPGLIB_DUMMYSCENE_H
#define RPGLIB_DUMMYSCENE_H
#include "RPGScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/*  */
		class DummyScene : public RPGScene{
		public:
			DummyScene(const std::string& id, SceneScript* mainscript);
			~DummyScene();
			
			void ReadyShow(Engine::ESceneArgs& params) override;
			void Update(Engine::keyboard_state& state) override;
			
			/* I need to implement these methods because I'm inheriting from EScene and not RPGScene */
			void Start() override;
			void Enter() override;
			void Load() override;
			void Load(RPGFactory& factory) override;
			void Unload() override;
			void Exit() override;
			void ReadyStandBy(Engine::ESceneArgs& params) override;
			void StandBy() override;
			void Focus() override;
			void Draw() override;
			void End() override;
		/* ----------------------------------------------------------------------------------- */
		protected:
			
		};
	}
}
#endif