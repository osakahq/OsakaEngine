 #include "stdafx.h"
#ifndef RPGLIB_STARTMENUSCENESCRIPT_H
#define RPGLIB_STARTMENUSCENESCRIPT_H
#include "rpglib_include.h"
#include "SceneScript.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class StartMenuSceneScript : public SceneScript {
		public:
			StartMenuSceneScript(RPGApplication* app);
			virtual ~StartMenuSceneScript();
			
			void Ready(Engine::ESceneArgs& params) override;

			const std::string mainlayer_id;
		protected:
			
		private:
			
		};
	}
}

#endif;