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

			/* */
			void SetLayers(std::string layer1);
			void Ready(Engine::ESceneArgsPTR& params) override;
		protected:
			
		private:
			
			/*  */
			std::string layer1;
		};
	}
}

#endif;