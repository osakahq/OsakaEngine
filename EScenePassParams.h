 #include "stdafx.h"
#ifndef ENGINE_ESCENEPASSPARAMS_H
#define ENGINE_ESCENEPASSPARAMS_H

namespace Osaka{
	namespace Engine{
		class EScenePassParams{
		public:
			EScenePassParams();
			virtual ~EScenePassParams();
		private:
			
		};
		//extern EScenePassParams EmptyScenePassParams;
		extern std::shared_ptr<EScenePassParams> EmptyScenePassParamsPTR;

	}
}
#endif