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
			
			//For their explanation see `EScene.h`
			virtual void Load() = 0;
			virtual void Unload() = 0;
			virtual void Show(Engine::ESceneArgsPTR& params) = 0;
			virtual void Hide() = 0;
			virtual void StandBy() = 0;
			virtual void StandBy(Engine::ESceneArgsPTR& params) = 0;
			virtual void Focus() = 0;
			virtual void Update() = 0;
			virtual void Draw() = 0;

			/* Called by RPGApplication (exitgame,loadgame) */
			virtual void Reset() = 0;

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplicationPTR app;
		};
	}
}
#endif