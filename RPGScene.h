 #include "stdafx.h"
#ifndef RPGLIB_RPGSCENE_H
#define RPGLIB_RPGSCENE_H
#include "EScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class RPGScene : public Engine::EScene{
		public:
			RPGScene(std::string id, RPGApplicationPTR& app, CanvasPTR& canvas, UserInterfacePTR& ui, ScriptPTR& script);
			virtual ~RPGScene();
			virtual void _delete();
			
			//For their explanations see `EScene.h`
			virtual void Init();

			virtual void Load();
			virtual void Unload();

			virtual void ReadyStandBy(Engine::ESceneArgsPTR& params);
			virtual void ReadyShow(Engine::ESceneArgsPTR& params);
			virtual void Exit();

			virtual void StandBy();
			virtual void Focus();

			virtual void Update();
			virtual void Draw();

			std::string GetId();
		/* ----------------------------------------------------------------------------------- */
		protected:
			std::string  id;
			
			//Owner
			CanvasPTR canvas;
			UserInterfacePTR ui;
			ScriptPTR script;
			/* NOT Owner */
			RPGApplicationPTR app;

			bool focus;
			bool standby;
			bool instack;
			bool hidden; //This can only be set with `StandByHide()` by the scene itself

			/* This is a method if the scene wants to not render or update while there is another scene stacked on
			 * This is private because the only way the scene know it is not showing, its itself.
			 *	. Remember that each script knows what the other script does. Like I have been saying, in script code almost anything is valid 
			 * This may only be called after calling `Stack("newscene"); this->StandByHide();` 
			 * Just remember that EApplication will call `StandBy()` regardless. */
			void StandByHide();
		};
	}
}
#endif