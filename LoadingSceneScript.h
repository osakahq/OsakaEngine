 #include "stdafx.h"
#ifndef RPGLIB_LOADINGSCENESCRIPT_H
#define RPGLIB_LOADINGSCENESCRIPT_H
#include "rpglib_include.h"
#include "SceneScript.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class LoadingSceneScript : public SceneScript {
		public:
			LoadingSceneScript(RPGApplicationPTR& app, AssetManagerPTR& assetm);
			~LoadingSceneScript();
			void _delete() override;

			/* */
			void Init(std::string fadelayer_id, RPGScenePTR& scene_parent);

			/* This is called from stack(from RPGApplication) */
			void Ready(Engine::ESceneArgsPTR& params) override;
			
			/* This function is accesed by the other loading thread.
			 * It is called inside the anonymous function that this class sets on GameLoader function */
			void LoadCompleted();
			bool isLoadCompleted();
		protected:
			
		private:
			/* volatile because this variable changes in 2 different threads */
			volatile bool loadCompleted;
			/* NOT Owner */
			AssetManagerPTR assetm;

			/* NOT Owner. Ownership is inside base class unorderedmap */
			std::string fadelayer_id;
		};
	}
}

#endif;