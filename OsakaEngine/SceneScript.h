#include "stdafx.h"
#ifndef RPGLIB_SCENESCRIPT_H
#define RPGLIB_SCENESCRIPT_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class SceneScript{
		public:
			SceneScript(RPGApplication* app);
			virtual ~SceneScript();
			
			virtual void Init(RPGScene* scene_parent);
			virtual void Load(RPGFactory& factory);
			virtual void Unload();

			virtual void Enter();
			virtual void Ready(Engine::ESceneArgs& args);
			virtual void Exit();

			virtual void Show();
			virtual void StandBy();
			virtual void Focus();

			virtual void Update(Engine::keyboard_state& state);
			virtual void End();
			
			/* NOT Owner */
			RPGApplication* app;
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner. EApplication has ownership */
			RPGScene* scene_parent;
			
		};
	}
}
#endif