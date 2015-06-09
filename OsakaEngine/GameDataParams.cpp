 #include "stdafx.h"

#include "GameData.h"
#include "GameDataParams.h"

namespace Osaka{
	namespace RPGLib{

		GameDataParams::GameDataParams(GameDataPTR& data){
			this->data = data;
		}
		GameDataParams::~GameDataParams(){
		}
		void GameDataParams::_delete(){
			data = nullptr;
		}

		void GameDataParams::SetParams(){
			//default values
			engine_logo = "engine_logo";
			gamestudio_logo = "gamestudio_logo";
			intro_song = "s_startmenu";
		}

		void GameDataParams::GetMapData(std::string map_id){
			//TODO
		}
	}
}