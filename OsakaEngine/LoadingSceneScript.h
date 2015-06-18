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
			LoadingSceneScript(RPGApplication* app, AssetManager* assetm);
			~LoadingSceneScript();
			
			/* This is called from stack(from RPGApplication) */
			void Ready(Engine::ESceneArgs& params) override;
			
			/* This function is accesed by the other loading thread.
			 * It is called inside the anonymous function that this class sets on GameLoader function */
			void LoadCompleted();
			bool isLoadCompleted();

			const std::string fadelayer_id;
		protected:
			
		private:
			/* volatile because this variable changes in 2 different threads */
			volatile bool loadCompleted;
			/* NOT Owner */
			AssetManager* assetm;

		};
	}
}

#endif;