#include "stdafx.h"
#ifndef RPGLIB_GAMDATAEINCLUDE_H
#define RPGLIB_GAMEDATAINCLUDE_H
#include "engine_include.h"
namespace Osaka{
	namespace RPGLib{
		/*
		 * Declarations are fine in this file because this header file is only included in CPP files
		 * */
		struct SoundType{
			SoundType(){}
			enum Value{
				BGM, Effect	
			};
		};
		struct AssetLoadingType{
			AssetLoadingType(){}
			enum Value{
				/* TODO: Copy the explanation of these types that is in the tests\runall xml file */
				NOT_SET, FULL_LOAD_STARTUP, SMARTLOAD_PARCIAL_NOUNLOAD, SMARTLOAD_FULL_NOUNLOAD, SMARTLOAD
			};
		};
		struct AssetType{
			enum Value{
				NOT_SET, TEXTURE, SOUND, VIDEO
			};
		};
		
		/* Per asset inside init-load node */
		struct asset_initload_data{
			asset_initload_data(){};
			std::string id;
			//Asset type is in Global asset list (see GameData.h)
		};
		//----------------------------------------------------------------------------------------------------
			/* This is per asset inside scene node */
			struct scene_asset_data{
				scene_asset_data(): always_load_unload(false){}
				std::string id;
				//Asset type is in Global asset list (see GameData.h)
				/* This params overrides the AssetLoadingType. Mostly for heavy stuff like video */
				bool always_load_unload;
			};
			/* Per related scene in related-scenes node */
			struct related_scene_data{
				related_scene_data(): linked(false), always_load(false), when_switch_unload_self(false){}
				std::string id;
				bool linked;
				bool always_load;
				bool when_switch_unload_self;
			};
		struct scene_data{
			scene_data(){};
			std::string id;
			std::unordered_map<std::string, scene_asset_data> assets;
			std::unordered_map<std::string, related_scene_data> related_scenes_data;
		};
		//----------------------------------------------------------------------------------------------------

		struct battle_data{
			battle_data(){};
		};
		struct character_data{
			character_data(){};
		};
		struct credits_data{
			credits_data(){};
		};
		struct enemy_data{
			enemy_data(){};
		};
		struct fontcharacter_data{
			fontcharacter_data(){};
			std::string id; //Example: A
			std::string sprite; //Example: font_A
		};
		struct instance_data{
			instance_data(){};
		};
		struct loadgame_data{
			loadgame_data(){};
		};
		struct npc_data{
			npc_data(){};
		};
		struct savegame_data{
			savegame_data(){};
		};
		struct sound_data{
			sound_data(){};
			std::string id;
			SoundType::Value type;
			std::string filename;
		};
		struct spell_data{
		};
		/* ------------------------------------------------------------------ */
		struct sprite_data{
			sprite_data(){};
			std::string id;
			std::string belongs_to_texture;
			SDL_Rect clip;
		};
		struct spritemap_data{
			spritemap_data(){}
			std::string id;
			std::string filename;
			Engine::RGB_HEX colorkey;
			std::unordered_map<std::string, sprite_data> sprites;
		};
		/* ------------------------------------------------------------------ */
		struct startmenu_data{
			startmenu_data(){};
			std::string background_sprite;
			std::string title_sprite;
			std::string subtitle_sprite;

			std::string loadgame_screen;
			std::string savegame_screen;
			std::string options_screen;
		};
		struct stat_data{
			stat_data(){};
		};
		struct video_data{
			video_data(){};
		};
		struct world_data{
			world_data(){};
		};

		/* Sample game session. */
		struct gamesession_data{
			gamesession_data(){};
		};
	}
}
#endif