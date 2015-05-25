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
			InitScene(RPGApplicationPTR& app);
			virtual ~InitScene();
			virtual void _delete();
			
			virtual void Init();

			virtual void Load();
			virtual void Unload();

			virtual void Show(Engine::ESceneArgsPTR& params);
			virtual void Hide();
			virtual void StandBy();
			virtual void StandBy(Engine::ESceneArgsPTR& params);
			virtual void Focus();

			virtual void Update();
			virtual void Draw();

			std::string GetId();
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplicationPTR app;

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