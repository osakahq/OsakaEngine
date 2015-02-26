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
			std::string  id;
			
			//For their explanations see `EScene.h`
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

			/* Scenes need to resetted everytime in RPGApp LoadGame/ExitGame is called, in other words, whenever GameSessionManager changes state 
			 *	. It is up to the script if it wants to do anything. */
			virtual void Reset();

		/* ----------------------------------------------------------------------------------- */
		protected:
			//Owner
			CanvasPTR canvas;
			UserInterfacePTR ui;
			ScriptPTR script;
			/* NOT Owner */
			RPGApplicationPTR app;

			/* This is an optional method if the scene wants to not render or update while there is another scene stacked on
			 * This is private because the only way the scene know it is not showing, its itself.
			 *	. Remember that each script knows what the other script does. Like I have been saying, in script code almost anything is valid 
			 * This may only be called after calling `Stack("newscene"); this->StandByHide();` 
			 * Just remember that EApplication will call `StandBy()` regardless. */
			virtual void StandByHide();
		};
	}
}
#endif