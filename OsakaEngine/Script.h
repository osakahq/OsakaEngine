#include "stdafx.h"
#ifndef RPGLIB_SCRIPT_H
#define RPGLIB_SCRIPT_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class Script{
		public:
			Script(RPGApplication* app, RPGScene* scene_parent);
			virtual ~Script();
			
			virtual void Init(Layer* layer_parent);
			virtual void Load(RPGFactory& factory);
			virtual void Unload();

			virtual void Enter();
			virtual void Ready(LayerArgs& args);
			virtual void Exit();

			virtual void Show();
			virtual void StandBy();
			virtual void Focus();

			virtual void Update() = 0;

			virtual void End();
			
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplication* app;
			/* NOT Owner */
			RPGScene* scene_parent;
			/* NOT Owner */
			Layer* layer_parent;
			/* Owner */
			Component::Registree* registree;
			
		private:
			bool __init;
		};
	}
}
#endif