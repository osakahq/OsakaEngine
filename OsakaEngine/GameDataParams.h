 #include "stdafx.h"
#ifndef RPGLIB_GAMEDATAPARAMS_H
#define RPGLIB_GAMEDATAPARAMS_H

#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		
		/* This class holds the params (engine_logo, gamestudio_logo, music, etc.)
		 * Instead of creating those params inside the data.xml file, it is easier to have them here, as a class.
		 * This class will be passed to the load function (inside RPGFactory class) */
		class GameDataParams {
		public:
			GameDataParams(GameData* data);
			virtual ~GameDataParams();
			
			virtual void SetParams();

			/* All of these are ids */
			std::string engine_logo;
			std::string gamestudio_logo;
			std::string intro_song;

			/* TODO: obviously it isnt a void
			 * This function is to help create various map scenes with 1 SceneBuilder and 1 MapScene */
			void GetMapData(const std::string& map_id);
		protected:
			/* NOT Owner */
			GameData* data;
		private:
			
		};
	}
}

#endif;