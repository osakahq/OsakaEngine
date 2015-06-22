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
		}
		GameData::~GameData(){
			for(auto it = assets_initload.begin();	it != assets_initload.end(); ++it){ delete it->second; }
			for(auto it = assets_scenes.begin();	it != assets_scenes.end(); ++it){ delete it->second; }

			for(auto it = battles.begin();			it != battles.end(); ++it){ delete it->second; }
			for(auto it = characters.begin();		it != characters.end(); ++it){ delete it->second; }
			for(auto it = credits.begin();			it != credits.end(); ++it){ delete it->second; }
			for(auto it = enemies.begin();			it != enemies.end(); ++it){ delete it->second; }
			for(auto it = instances.begin();		it != instances.end(); ++it){ delete it->second; }
			for(auto it = npcs.begin();				it != npcs.end(); ++it){ delete it->second; }
			for(auto it = spells.begin();			it != spells.end(); ++it){ delete it->second; }

			for(auto it = stats.begin();			it != stats.end(); ++it){ delete it->second; }
			for(auto it = videos.begin();			it != videos.end(); ++it){ delete it->second; }
			for(auto it = worlds.begin();			it != worlds.end(); ++it){ delete it->second; }

			for(auto it = fontmap.begin();			it != fontmap.end(); ++it){ delete it->second; }
			for(auto it = sounds.begin();			it != sounds.end(); ++it){ delete it->second; }
			for(auto it = spritemaps.begin();		it != spritemaps.end(); ++it){ delete it->second; }
			for(auto it = sprite_ids.begin();		it != sprite_ids.end(); ++it){ delete it->second; }
			for(auto it = gamesessions.begin();		it != gamesessions.end(); ++it){ delete it->second; }

			assets_type.clear();
			assets_initload.clear();
			assets_scenes.clear();

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

			fontmap.clear();
			
			sounds.clear();
			spritemaps.clear();
			gamesessions.clear();
			sprite_ids.clear();
		}
		
	}
}