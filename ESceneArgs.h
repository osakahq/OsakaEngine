 #include "stdafx.h"
#ifndef ENGINE_ESCENEARGS_H
#define ENGINE_ESCENEARGS_H

namespace Osaka{
	namespace Engine{

		class ESceneArgs{
		public:
			ESceneArgs();
			virtual ~ESceneArgs();
		private:
			
		};

		extern std::shared_ptr<ESceneArgs> EmptyESceneArgsPTR;

	}
}
#endif