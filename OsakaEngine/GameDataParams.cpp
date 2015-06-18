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
			engine_logo = "engine_logo";
			gamestudio_logo = "gamestudio_logo";
			intro_song = "s_startmenu";
		}

		void GameDataParams::GetMapData(const std::string& map_id){
			//TODO
		}
	}
}