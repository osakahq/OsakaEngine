#include "stdafx.h"
#include "gamedata_include.h"
#include "GameData.h"
namespace Osaka{
	namespace RPGLib{
		GameData::GameData(){
			vsync = true;
			time_per_frame = 16; //60 fps
			target_fps = 60;
			max_updates_catch_up = 10; //160ms max time for delta
			asset_loading_type = AssetLoadingType::NOT_SET;
			sounds = std::make_shared<std::unordered_map<std::string, sound_dataPTR>>();
			spritemaps = std::make_shared<std::unordered_map<std::string, spritemap_dataPTR>>();
			sprite_ids = std::make_shared<std::unordered_map<std::string, sprite_dataPTR>>();
			gamesessions = std::make_shared<std::unordered_map<std::string, gamesession_dataPTR>>();

			assets_type = std::make_shared<std::unordered_map<std::string, unsigned int>>();	
			assets_initload = std::make_shared<std::unordered_map<std::string, asset_initload_dataPTR>>();
			assets_scenes = std::make_shared<std::unordered_map<std::string, scene_dataPTR>>();

			fontmap = std::make_shared<std::unordered_map<char, fontcharacter_dataPTR>>();
		}
		GameData::~GameData(){
#ifdef _DEBUG
			_CHECKDELETE("GameData");
#endif
		}
		void GameData::_delete(){
#ifdef _DEBUG
			_CHECKDELETE("GameData_delete");
#endif
			battles.clear();
			characters.clear();
			credits.clear();
			enemies.clear();
			instances.clear();
			npcs.clear();
			spells.clear();
			stats.clear();
			videos.clear();
			worlds.clear();

			fontmap->clear(); fontmap = nullptr;
			
			//This is only needed when the structs have a PTR to free.
			//for(auto it = sounds->begin(); it != sounds->end(); ++it ) it->second->_delete();
			sounds->clear(); sounds = nullptr;
			spritemaps->clear(); spritemaps = nullptr;
			gamesessions->clear(); gamesessions = nullptr;
			sprite_ids->clear(); sprite_ids = nullptr;

			assets_type->clear(); assets_type = nullptr;
			assets_initload->clear(); assets_initload = nullptr;
			assets_scenes->clear(); assets_scenes = nullptr;
		}
	}
}