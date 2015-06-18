 #include "stdafx.h"
#ifndef RPGLIB_GAMEDATA_H
#define RPGLIB_GAMEDATA_H
#include "engine_include.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		struct battle_data;struct character_data;struct credits_data;struct enemy_data;
		struct instance_data;struct loadgame_data;struct npc_data;
		struct savegame_data;struct spell_data;
		struct startmenu_data;struct stat_data;struct video_data;struct world_data;

		class GameData{
		public:
			GameData();
			~GameData();
			std::string name;
			int window_width;
			int window_height;
			bool vsync;
			int time_per_frame; //in ms
			int target_fps;
			int max_updates_catch_up;
			//OWNER of all below
			//These screens are created in Ascension.cpp
			//startmenu_data*		startmenu;
			//loadgame_data*		loadgame;
			//savegame_data*		savegame;

			/* The color RGBA for default render color */
			Engine::RGBA_HEX default_render_color_data;

			/* loadingType = Enum: AssetLoadingType */
			unsigned int asset_loading_type;
			/* Global asset list with type. This holds all the assets (sounds, textures, video and with their corresponding type) */
			std::unordered_map<std::string, unsigned int>				assets_type;
			std::unordered_map<std::string, asset_initload_data*>	assets_initload;
			std::unordered_map<std::string, scene_data*>				assets_scenes;

			std::unordered_map<std::string, battle_data*>		battles;
			std::unordered_map<std::string, character_data*>	characters;
			std::unordered_map<std::string, credits_data*>		credits;
			std::unordered_map<std::string, enemy_data*>		enemies;
			std::unordered_map<std::string, instance_data*>		instances;
			std::unordered_map<std::string, npc_data*>			npcs;
			std::unordered_map<std::string, spell_data*>		spells;
			
			std::unordered_map<std::string, stat_data*>			stats;
			std::unordered_map<std::string, video_data*>		videos;
			std::unordered_map<std::string, world_data*>		worlds;

			std::string fontmap_error;
			int fontmap_space_x;
			int fontmap_space_y;
			/* Because the function we use to read the xml file is only char, we can only accept char */
			std::unordered_map<char, fontcharacter_data*>	fontmap;

			std::unordered_map<std::string, sound_data*>		sounds;
			std::unordered_map<std::string, spritemap_data*>	spritemaps;
				/* This one contains id of the sprite and id of the spritemap(texture).
				 * So I can search for it easily in `spritemaps` */
				std::unordered_map<std::string, sprite_data*> sprite_ids;

			/* Sample gamesessions. */
			std::unordered_map<std::string, gamesession_data*>	gamesessions;
		/* ----------------------------------------------------------------------------------- */
		private:
			
		};
		
	}
}
#endif