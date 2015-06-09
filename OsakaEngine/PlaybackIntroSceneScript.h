 #include "stdafx.h"
#ifndef RPGLIB_PLAYBACKINTROSCENESCRIPT_H
#define RPGLIB_PLAYBACKINTROSCENESCRIPT_H
#include "rpglib_include.h"
#include "SceneScript.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class PlaybackIntroSceneScript : public SceneScript {
		public:
			PlaybackIntroSceneScript(RPGApplicationPTR& app);
			~PlaybackIntroSceneScript();
			void _delete() override;

			void Enter() override;
			void Ready(Engine::ESceneArgsPTR& params) override;

			/* These are set inside the constructor */
			std::string mainlayer_id;
			std::string fadelayer_id;
		protected:
			
		private:
			
		};
	}
}

#endif;