 #include "stdafx.h"
#ifndef RPGLIB_RPGLOADINGSCENE_H
#define RPGLIB_RPGLOADINGSCENE_H
#include "rpglib_include.h"
#include "RPGScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class RPGLoadingScene : public RPGScene {
		public:
			RPGLoadingScene(std::string id, RPGApplicationPTR& app, CanvasPTR& canvas, UserInterfacePTR& ui, ScriptPTR& script, AssetManagerPTR& assetm);
			~RPGLoadingScene();
			void _delete() override;
			/* This function calls GameLoader function and adds itself to the loop as a normal EScene */
			void StartTransition(const char* name, Engine::ESceneArgsPTR& params, TransitionType::Value type);
			/* This function is accesed by the other loading thread.
			 * It is called inside the anonymous function that this class sets on GameLoader function */
			void LoadCompleted();
			bool isLoadCompleted();
		private:
			/* volatile because this variable changes in 2 different threads */
			volatile bool loadCompleted;
			/* NOT Owner */
			AssetManagerPTR assetm;
		};
	}
}

#endif;