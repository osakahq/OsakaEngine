#include "stdafx.h"
#ifndef RPGLIB_SCRIPT_H
#define RPGLIB_SCRIPT_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class Script{
		public:
			Script(RPGApplicationPTR& app, RPGScenePTR& scene_parent);
			virtual ~Script();
			virtual void _delete();
			
			virtual void Init(LayerPTR& layer_parent);
			virtual void Load();
			virtual void Unload();

			virtual void Ready(LayerArgsPTR& args);
			virtual void Exit();

			virtual void Show();
			virtual void StandBy();
			virtual void Focus();

			virtual void Update() = 0;
			
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplicationPTR app;
			/* NOT Owner */
			RPGScenePTR scene_parent;
			/* NOT Owner */
			LayerPTR layer_parent;
			
		};
	}
}
#endif