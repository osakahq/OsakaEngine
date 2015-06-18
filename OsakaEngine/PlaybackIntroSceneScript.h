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
			PlaybackIntroSceneScript(RPGApplication* app);
			~PlaybackIntroSceneScript();
			
			void Enter() override;
			void Ready(Engine::ESceneArgs& params) override;

			/* These are set inside the constructor */
			const std::string mainlayer_id;
			const std::string fadelayer_id;
		protected:
			
		private:
			
		};
	}
}

#endif;