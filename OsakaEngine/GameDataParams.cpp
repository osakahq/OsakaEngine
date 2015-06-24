 #include "stdafx.h"

#include "GameData.h"
#include "GameDataParams.h"

namespace Osaka{
	namespace RPGLib{

		GameDataParams::GameDataParams(GameData* data){
			this->data = data;
		}
		GameDataParams::~GameDataParams(){
			data = NULL;
		}
		
		void GameDataParams::SetParams(){
			//default values

			scene_intro					= "playbackintro";
			scene_startmenu				= "startmenu";
			scene_startmenu_newgame		= "startmenu_playbacknewgame";
			scene_loadgame				= "loadgame";
			scene_savegame				= "savegame";
			scene_options				= "options";
			scene_credits				= "credits";

			sprite_engine_logo			= "engine_logo";
			sprite_gamestudio_logo		= "gamestudio_logo";
			music_intro_song			= "s_startmenu";

			sprite_startmenu_background = "startmenu_background";
			sprite_startmenu_title = "startmenu_title";
			sprite_startmenu_subtitle = "startmenu_subtitle";
		}

		void GameDataParams::GetMapData(const std::string& map_id){
			//TODO
		}
	}
}