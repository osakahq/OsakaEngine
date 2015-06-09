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
			StartMenuSceneScript(RPGApplicationPTR& app);
			virtual ~StartMenuSceneScript();
			void _delete() override;

			void Ready(Engine::ESceneArgsPTR& params) override;

			std::string mainlayer_id;
		protected:
			
		private:
			
		};
	}
}

#endif;