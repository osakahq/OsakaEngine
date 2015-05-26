#include "stdafx.h"
#ifndef RPGLIB_SCRIPT_H
#define RPGLIB_SCRIPT_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class Script{
		public:
			Script(RPGApplicationPTR& app);
			virtual ~Script();
			virtual void _delete();
			
			virtual void Init(RPGScenePTR& parent);
			//For their explanation see `EScene.h`
			virtual void Load();
			virtual void Unload();

			virtual void Ready(Engine::ESceneArgsPTR& params) = 0;
			virtual void Exit();

			virtual void Show();
			virtual void StandBy();
			virtual void Focus();

			virtual void Update() = 0;
			virtual void Draw();

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplicationPTR app;

			/* NOT Owner */
			RPGScenePTR parent;

			/* NOT Owner. Raw */
			SDL_Renderer* raw_renderer;
		};
	}
}
#endif