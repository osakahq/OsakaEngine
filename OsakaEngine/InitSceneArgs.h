 #include "stdafx.h"
#ifndef RPGLIB_INITSCENEARGS_H
#define RPGLIB_INITSCENEARGS_H
#include "rpglib_include.h"
#include "ESceneArgs.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		class InitSceneArgs : public Engine::ESceneArgs{
		public:
			InitSceneArgs() : Engine::ESceneArgs(){
				init_args = nullptr;
			};
			~InitSceneArgs(){
#ifdef _DEBUG
				_CHECKDELETE("InitSceneArgs");
#endif				
				init_args = nullptr;
			};

			/* Scene to init. */
			std::string scene;
			/* (There are no owners for Args). The args to send to the scene to switch. */
			Engine::ESceneArgsPTR init_args;
		private:
			
		};

	}
}
#endif