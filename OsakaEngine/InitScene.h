 #include "stdafx.h"
#ifndef RPGLIB_INITSCENE_H
#define RPGLIB_INITSCENE_H
#include "EScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/* This class is only a placeholder/(dummy scene) to switch to the real first scene. */
		class InitScene : public Engine::EScene{
		public:
			InitScene(RPGApplication* app);
			~InitScene();
			
			void ReadyShow(Engine::ESceneArgs& params) override;
			void Update() override;
			
			std::string GetId() override;

			/* I need to implement these methods because I'm inheriting from EScene and not RPGScene */
			void Start() override;
			void Enter() override;
			void Load() override;
			void Unload() override;
			void Exit() override;
			void ReadyStandBy(Engine::ESceneArgs& params) override;
			void StandBy() override;
			void Focus() override;
			void Draw() override;
			void End() override;
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplication* app;

			/* (There are no owners for Args). This is the params to start the first scene */
			Engine::ESceneArgsPTR init_args;

			/* The initial id scene */
			std::string scene;

			/* Call transition? */
			bool callTransition;
		};
	}
}
#endif