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
			DummyScene(std::string id, SceneScriptPTR& mainscript);
			~DummyScene();
			void _delete() override;
			
			void ReadyShow(Engine::ESceneArgsPTR& params) override;
			void Update() override;
			
			std::string GetId() override;

			/* I need to implement these methods because I'm inheriting from EScene and not RPGScene */
			void Start() override;
			void Enter() override;
			void Load() override;
			void Load(RPGFactoryPTR& factory) override;
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