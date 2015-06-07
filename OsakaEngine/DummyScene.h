 #include "stdafx.h"
#ifndef RPGLIB_DUMMYSCENE_H
#define RPGLIB_DUMMYSCENE_H
#include "EScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/*  */
		class DummyScene : public Engine::EScene{
		public:
			DummyScene(std::string id);
			~DummyScene();
			void _delete() override;
			
			void ReadyShow(Engine::ESceneArgsPTR& params) override;
			void Update() override;
			
			std::string GetId() override;

			/* I need to implement these methods because I'm inheriting from EScene and not RPGScene */
			void Enter() override;
			void Load() override;
			void Unload() override;
			void Exit() override;
			void ReadyStandBy(Engine::ESceneArgsPTR& params) override;
			void StandBy() override;
			void Focus() override;
			void Draw() override;
			void End() override;
		/* ----------------------------------------------------------------------------------- */
		protected:
			std::string id;
		};
	}
}
#endif