#include "stdafx.h"
#ifndef RPGLIB_SCENESCRIPT_H
#define RPGLIB_SCENESCRIPT_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class SceneScript{
		public:
			SceneScript(RPGApplicationPTR& app);
			virtual ~SceneScript();
			virtual void _delete();
			
			virtual void Init(RPGScenePTR& scene_parent);
			virtual void Load();
			virtual void Unload();

			virtual void Ready(Engine::ESceneArgsPTR& args);
			virtual void Exit();

			virtual void Show();
			virtual void StandBy();
			virtual void Focus();

			virtual void Update();
			
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplicationPTR app;
			/* NOT Owner */
			RPGScenePTR scene_parent;
			
		};
	}
}
#endif