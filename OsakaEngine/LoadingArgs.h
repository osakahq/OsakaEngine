 #include "stdafx.h"
#ifndef RPGLIB_LOADINGARGS_H
#define RPGLIB_LOADINGARGS_H
#include "rpglib_include.h"
#include "ESceneArgs.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		class LoadingArgs : public Engine::ESceneArgs{
		public:
			LoadingArgs();
			~LoadingArgs();

			/* This is the id of the scene to switch or stack after the loading process has completed */
			std::string scene;
			/* NOT Owner. This is the params that the initial script sent to the next screen */
			Engine::ESceneArgsPTR send_params;
			/* The type (switch or stack). This value comes originally from script->rpgapp->Switch/StackTransition */
			TransitionType::Value type;
		private:
			
		};
		typedef std::shared_ptr<LoadingArgs> LoadingArgsPTR;
	}
}
#endif