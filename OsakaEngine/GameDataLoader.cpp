 #include "stdafx.h"
#include "Utils.h"
#include "Debug.h"
#include "engine_include.h"
#include "gamedata_include.h"
#include "GameData.h"
#include "Factory.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "GameDataLoader.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{

		GameDataLoader::GameDataLoader(Debug::Debug* debug){
			this->debug = debug;
		}
		GameDataLoader::~GameDataLoader(){
#ifdef _DEBUG
			_CHECKDELETE("GameDataLoader");
#endif		
			debug = NULL;
		}
		
		void GameDataLoader::LoadGameFile(const char* filename, GameData& data){
			//GameDataPTR data = factory->CreateGameData();

			rapidxml::xml_document<> doc;
			rapidxml::file<> xmlFile(filename); //Char
			doc.parse<0>(xmlFile.data());
			
			rapidxml::xml_node<>* root = doc.first_node("game");
			data.name = root->first_attribute("name")->value();
			
			data.window_width = std::stoi(std::string(root->first_attribute("width")->value()));
			data.window_height = std::stoi(std::string(root->first_attribute("height")->value()));
			
			data.vsync = GetTrueFalse(root->first_attribute("vsync")->value());
			data.time_per_frame = std::stoi(std::string(root->first_attribute("time-per-frame")->value()));
			data.target_fps = std::stoi(std::string(root->first_attribute("target-fps")->value()));

			data.max_updates_catch_up = std::stoi(std::string(root->first_attribute("max-updates-catch-up")->value()));

			std::string linefeed;
			/* This is needed because SplitString doesn't behave as a normal split function. "\r\n" is taking as 2 separate tokens
			 * For some reason if the file has \r\n and linefeed='\n', it bugs out. */
			if(strcmp(GAMEDATA_LINEFEED_WINDOWS, root->first_attribute("linefeed")->value()) == 0){
				linefeed = "\r\n";
				debug->l("[GameData] linefeed is \\r\\n");
			}else{
				linefeed = "\n";
				debug->l("[GameData] linefeed is \\n");
			}
			
			std::string loadin_type = root->first_node("asset-map")->first_attribute("loading")->value();
			if( strcmp(loadin_type.c_str(), "FULL_LOAD_STARTUP") == 0 ){
				data.asset_loading_type = AssetLoadingType::FULL_LOAD_STARTUP;
			}else if( strcmp(loadin_type.c_str(), "SMARTLOAD_PARCIAL_NOUNLOAD") == 0 ){
				data.asset_loading_type = AssetLoadingType::SMARTLOAD_PARCIAL_NOUNLOAD;
			}else if( strcmp(loadin_type.c_str(), "SMARTLOAD_FULL_NOUNLOAD") == 0 ){
				data.asset_loading_type = AssetLoadingType::SMARTLOAD_FULL_NOUNLOAD;
			}else if( strcmp(loadin_type.c_str(), "SMARTLOAD") == 0 ){
				data.asset_loading_type = AssetLoadingType::SMARTLOAD;
			}

			rapidxml::xml_node<>* drc_node = root->first_node("default-render-color");
			data.default_render_color_data.r = std::stoi(drc_node->first_node("r")->value());
			data.default_render_color_data.g = std::stoi(drc_node->first_node("g")->value());
			data.default_render_color_data.b = std::stoi(drc_node->first_node("b")->value());
			data.default_render_color_data.a = std::stoi(drc_node->first_node("a")->value());
			
			debug->l("[GameData] Loading asset-map:\"init-load\" data...");
				LoadInitialAssetmap(data, *root->first_node("asset-map")->first_node("init-load"));
			
			/* This is a temporary variable, because the group data is inserted into the scene data. */
			unorderedmap_group_data groups;
			if( root->first_node("asset-map")->first_node("groups") != NULL ){
				debug->l("[GameData] Loading asset-map:\"groups\"...");
				LoadAssetGroups(groups, *root->first_node("asset-map")->first_node("groups"));
			}
			
			debug->l("[GameData] Loading asset-map:\"scenes\"data...");
				LoadScenesAssetmap(groups, data, *root->first_node("asset-map")->first_node("scenes"));
			for(auto it = groups.begin(); it != groups.end(); ++it){
				/* We need to delete them because when we pass them to the real map, we copy the values. */
				delete it->second;
			}
			groups.clear();

			debug->l("[GameData] Loading sprites map data...");
				LoadSpritemaps(data, *root->first_node("spritemaps"), linefeed);

			debug->l("[GameData] Loading sound data...");
				LoadSounds(data, *root->first_node("sounds"));

			debug->l("[GameData] Loading fontmap data...");
				LoadFontmap(data, *root->first_node("fontmap"));

		}

		void GameDataLoader::LoadInitialAssetmap(GameData& data, rapidxml::xml_node<>& init_load_node){
			//Inside asset-map > init-load node
			asset_initload_data* asset_data;
			for(rapidxml::xml_node<>* asset_node = init_load_node.first_node(); asset_node != NULL; asset_node = asset_node->next_sibling("asset")){
				asset_data = new asset_initload_data();
				asset_data->id = asset_node->first_attribute("id")->value();
				//asset_data->type = (AssetType::Value)GameDataLoader::GetAssetType(asset_node->Attribute("type"));
				auto it_assets_initload = data.assets_initload.insert(std::make_pair(asset_data->id,asset_data));
				if( !it_assets_initload.second ){
					debug->e("[GameDataLoader] Failed to insert asset. ID: " + asset_data->id);
				}
			}
		}

		void GameDataLoader::LoadAssetGroups(unorderedmap_group_data& groups, rapidxml::xml_node<>& groups_node){
			//group_dataPTR = scene_dataPTR (typedef)

			//For each group in groups node
			group_data* group;
			for(rapidxml::xml_node<>* group_node = groups_node.first_node(); group_node != NULL; group_node = group_node->next_sibling("group")){
				group = new scene_data();
				group->id = group_node->first_attribute("id")->value();

				//For each asset node in scene > assets node
				if( group_node->first_node("assets") != NULL ){
					for(rapidxml::xml_node<>* asset_node = group_node->first_node("assets")->first_node("asset"); asset_node != NULL; asset_node = asset_node->next_sibling("asset")){
						scene_asset_data scene_asset;
						scene_asset.id = asset_node->first_attribute("id")->value();
						if( asset_node->first_attribute("always-load-unload") != NULL ){
							scene_asset.always_load_unload = GetTrueFalse(asset_node->first_attribute("always-load-unload")->value());
						}
						group->assets[scene_asset.id] = scene_asset;
					}
				}
				//For each related scene node in scene > related scenes
				if( group_node->first_node("related-scenes") != NULL ){
					for(rapidxml::xml_node<>* r_scene_node = group_node->first_node("related-scenes")->first_node("scene"); 
						r_scene_node != NULL; r_scene_node = r_scene_node->next_sibling("scene") 
					){
						related_scene_data related_scene;
						SetRelatedScene(&related_scene, *r_scene_node);
						group->related_scenes_data[related_scene.id] = related_scene;
					}
				}
				//insert the group into the group list
				auto it_groups = groups.insert(std::make_pair(group->id, group));
				if( !it_groups.second ){
					debug->e("[GameDataLoader] Failed to insert group. ID: " + group->id);
				}
			}
		}

		void GameDataLoader::LoadScenesAssetmap(unorderedmap_group_data& groups, GameData& data, rapidxml::xml_node<>& scenes_node){
			//Inside asset-map > scenes node

			//For each scene node in scenes node
			scene_data* scene_d;
			for(rapidxml::xml_node<>* scene_node = scenes_node.first_node(); scene_node != NULL; scene_node = scene_node->next_sibling("scene")){
				scene_d = new scene_data();
				scene_d->id = scene_node->first_attribute("id")->value();
				
				//For each asset node in scene > assets node
				if( scene_node->first_node("assets") != NULL ){
					for(rapidxml::xml_node<>* asset_node = scene_node->first_node("assets")->first_node("asset"); asset_node != NULL; asset_node = asset_node->next_sibling("asset")){
						scene_asset_data scene_asset;
						scene_asset.id = asset_node->first_attribute("id")->value();
						//scene_asset.type = (AssetType::Value)GameDataLoader::GetAssetType(asset_node->Attribute("type"));
						if( asset_node->first_attribute("always-load-unload") != NULL ){
							scene_asset.always_load_unload = GetTrueFalse(asset_node->first_attribute("always-load-unload")->value());
						}
					
						scene_d->assets[scene_asset.id] = scene_asset;
					}
				}
				
				//For each related scene node in scene > related scenes
				if( scene_node->first_node("related-scenes") != NULL ){
					for(rapidxml::xml_node<>* related_scene_node = scene_node->first_node("related-scenes")->first_node("scene"); 
						related_scene_node != NULL; 
						related_scene_node = related_scene_node->next_sibling("scene")
					){
						related_scene_data related_scene;
						SetRelatedScene(&related_scene, *related_scene_node);
						
						scene_d->related_scenes_data[related_scene.id] = related_scene;
					}
				}
				
				/* Shortcut for a group id. <scene id="id" group-id="id" */
				if( scene_node->first_attribute("group-id") != NULL ){
					CopyGroupData(scene_d, *groups.at(scene_node->first_attribute("group-id")->value()));
				}
				//For each group in groups node
				if( scene_node->first_node("groups") != NULL ){
					for(rapidxml::xml_node<>* group_node = scene_node->first_node("groups")->first_node("group"); group_node != NULL; group_node = group_node->next_sibling("group")
					){
						CopyGroupData(scene_d, *groups.at(group_node->first_attribute("id")->value()));
					}
				}

				auto it_assets_scenes = data.assets_scenes.insert(std::make_pair(scene_d->id, scene_d));
				if( !it_assets_scenes.second ){
					debug->e("[GameDataLoader] Failed to insert scene. ID: " + scene_d->id);
				}
			}

		}

		/* Helper functions: It modifies the struct scene_data */
		void GameDataLoader::CopyGroupData(scene_data* scene_d, const group_data& group_data){
			//We don't really need to check if insert succeded because, if there are duplicates, we don't really care.
			scene_d->assets.insert(group_data.assets.begin(), group_data.assets.end());
			scene_d->related_scenes_data.insert(group_data.related_scenes_data.begin(), group_data.related_scenes_data.end());
		}

		/* Helper functions: It modifies the struct */
		void GameDataLoader::SetRelatedScene(related_scene_data* related_scene, rapidxml::xml_node<>& related_scene_node){
			related_scene->id = related_scene_node.first_attribute("id")->value();
			related_scene->linked		= GetTrueFalse(related_scene_node.first_attribute("linked")->value());
			related_scene->always_load	= GetTrueFalse(related_scene_node.first_attribute("always-load")->value());

			//if( related_scene_node.first_attribute("when-switch-unload-self") != NULL ){
			//	related_scene->when_switch_unload_self = GetTrueFalse(related_scene_node.first_attribute("when-switch-unload-self")->value());
			//}

			if( related_scene->linked && related_scene->always_load == false ){
				debug->e("[GameDataLoader:SetRelatedScene] Related scene \""+related_scene->id+"\" data has contradictory settings (linked and always-load)");
			}
		}

		/* Helper function */
		unsigned int GameDataLoader::GetAssetType(const char* type){
			if( strcmp(type, "sound") == 0 ){
				return AssetType::SOUND;
			}else if( strcmp(type, "texture") == 0 ){
				return AssetType::TEXTURE;
			}else if( strcmp(type, "video") == 0 ){
				return AssetType::VIDEO;
			}
			debug->e("[GameDataLoader] Unkown Asset Type");
			return AssetType::NOT_SET; //Never reaches.
		}
		/* Helper function */
		bool GameDataLoader::GetTrueFalse(const char* text){
			if( strcmp(text, "false") == 0 ){
				return false;
			}else if( strcmp(text, "true") == 0 ){
				return true;
			}
			debug->e("[GameDataLoader] Unkown True or false type");
			return false;
		}

		void GameDataLoader::LoadSounds(GameData& data, rapidxml::xml_node<>& sounds_node){
			//Inside <sounds> node
			sound_data* sound;
			for(rapidxml::xml_node<>* sound_node = sounds_node.first_node(); sound_node != NULL; sound_node = sound_node->next_sibling("sound")){
				sound = new sound_data();
				sound->filename = sound_node->first_attribute("filename")->value();
				sound->id = sound_node->first_attribute("id")->value();
				if( strcmp(sound_node->first_attribute("type")->value(), "bgm") == 0 ){
					sound->type = SoundType::BGM;
				}else{
					sound->type = SoundType::Effect;
				}
				auto it_assets_type = data.assets_type.insert(std::make_pair(sound->id, AssetType::SOUND));
				if( !it_assets_type.second ){
					debug->e("[GameDataLoader] Failed to type sound. ID: " + sound->id);
				}
				auto it_sounds = data.sounds.insert(std::make_pair(sound->id, sound));
				if( !it_sounds.second ){
					debug->e("[GameDataLoader] Failed to insert sound. ID: " + sound->id);
				}
			}
		}

		void GameDataLoader::LoadSpritemaps(GameData& data, rapidxml::xml_node<>& spritemaps_node, const std::string& linefeed){
			//spritemaps_node = <spritemapS> node
			
			//For each child in <spritemaps> node
			spritemap_data* spritemap;
			for(rapidxml::xml_node<>* spritemap_node = spritemaps_node.first_node(); spritemap_node != NULL; spritemap_node = spritemap_node->next_sibling("spritemap")){
				//We have a <spritemap> node
				
				//`spritemap` is always inserted in GameData->spritemaps
				spritemap = new spritemap_data();
				spritemap->filename = spritemap_node->first_attribute("filename")->value();
				spritemap->id = spritemap_node->first_attribute("id")->value();
				spritemap->colorkey.r = std::stoi(spritemap_node->first_attribute("colorkey-r")->value());
				spritemap->colorkey.g = std::stoi(spritemap_node->first_attribute("colorkey-g")->value());
				spritemap->colorkey.b = std::stoi(spritemap_node->first_attribute("colorkey-b")->value());
				
				//We add the texture asset to the global asset list
				auto it_assets_type = data.assets_type.insert(std::make_pair(spritemap->id, AssetType::TEXTURE));
				if( !it_assets_type.second ){
					debug->e("[GameDataLoader] Failed to insert spritemap. ID: " + spritemap->id);
				}

				std::vector<std::string> sprite_text;
				//Split it so have get: sprite_id = 0 0 32 32 / sprite_id2 = 32 32 32 32
				//spritemap_node->GetText() = we have the content of the <spritemap> node: sprite_id 0 0 32 32 \r\n sprite_id2 32 32 32 32 ...etc.
				Utils::SplitString(sprite_text, spritemap_node->value(), linefeed);
				
				//`temp_sprite` is copied when inserted.
				sprite_data temp_sprite;
				for( auto it = sprite_text.begin(); it != sprite_text.end(); ++it ){
					//We go through every string found:
					//	- sprite_id = 0 0 32 32
					//	- sprite_id2 = 32 32 32 32

					std::string str = Utils::TrimString((*it));
					//For some reason... Sometimes it can give me strings with no text (I guess it has to do with the \r\n,SplitString shenanigan)
					if( str.empty() )
						continue;

					//Here we split the string by '=' and we get id and coords.
					std::vector<std::string> spriteinfo_text;
					Utils::SplitString(spriteinfo_text, str, "=");
					if( spriteinfo_text.size() != 2 ){
						//This means that we didn't get what we expected: [sprite_id] / [0 0 32 32]
						debug->e("[GameDataLoader] Corrupted spritemap data.");
					}

					//at(0) = sprite_id
					//We have to strim it because of the space before = (spriteid[ ]= 0 0 32 32)
					temp_sprite.id = Utils::TrimString(spriteinfo_text.at(0));
					temp_sprite.belongs_to_texture = spritemap->id;

					std::vector<std::string> temp_coords;
					//at(1) = 0 0 32 32
					Utils::SplitString(temp_coords, spriteinfo_text.at(1), " ");
					//We split the string by 'space' at the end we set the sprite_data
					int coord_i = -1;
					for( auto it_coords = temp_coords.begin(); it_coords != temp_coords.end(); ++it_coords ){
						switch(++coord_i){
						case 0: temp_sprite.clip.x = stoi(*it_coords); break;
						case 1: temp_sprite.clip.y = stoi(*it_coords); break;
						case 2: temp_sprite.clip.w = stoi(*it_coords); break;
						case 3:
							temp_sprite.clip.h = stoi(*it_coords);
							//This is a copy. Inserts the sprite into the spritemap
							auto it_sprites = spritemap->sprites.insert(std::make_pair(temp_sprite.id, temp_sprite));
							if( !it_sprites.second ){
								debug->e("[GameDataLoader] Failed to insert sprite. ID: " + temp_sprite.id);
							}

							//Insert the id of the sprite and where it belongs (spritemap) so I can search them easily
							sprite_data* temp_spritePTR = new sprite_data();
							temp_spritePTR->id = temp_sprite.id;
							temp_spritePTR->belongs_to_texture = spritemap->id;
							temp_spritePTR->clip.x = temp_sprite.clip.x; temp_spritePTR->clip.y = temp_sprite.clip.y;
							temp_spritePTR->clip.w = temp_sprite.clip.w; temp_spritePTR->clip.h = temp_sprite.clip.h;

							auto it_sprite_ids = data.sprite_ids.insert(std::make_pair(temp_sprite.id, temp_spritePTR));
							if( !it_sprite_ids.second ){
								debug->e("[GameDataLoader] Failed to insert sprite (sprite_ids). ID: " + temp_sprite.id);
							}
							break;
						}
					}
					if( coord_i != 3 ){
						//This means we didn't get 4 numbers [0 0 32 32]
						debug->e("[GameDataLoader] Corrupted spritemap data. STAGE 2");
					}
				}
				//Inserts the spritemap into the spritemap list (spritemapS)
				auto it_spritemaps = data.spritemaps.insert(std::make_pair(spritemap->id, spritemap));
				if( !it_spritemaps.second ){
					debug->e("[GameDataLoader] Failed to insert spritemap. ID: " + spritemap->id);
				}
			}//End for (no more spritemapS)
		}
	
		void GameDataLoader::LoadFontmap(GameData& data, rapidxml::xml_node<>& fontmap_node){
			//Inside <fontmap> node

			data.fontmap_error = fontmap_node.first_attribute("error-sprite")->value();
			data.fontmap_space_x = std::stoi(fontmap_node.first_attribute("space-x")->value());
			data.fontmap_space_y = std::stoi(fontmap_node.first_attribute("space-y")->value());;

			fontcharacter_data* character;
			for(rapidxml::xml_node<>* character_node = fontmap_node.first_node(); character_node != NULL; character_node = character_node->next_sibling("character")){
				character = new fontcharacter_data();
				character->id = character_node->first_attribute("id")->value();
				character->sprite = character_node->first_attribute("sprite")->value();

				if( character->id.length() != 1 )
					debug->e("[GameDataLoader] ID fontmap sprite has to be 1 character (char)");

				char id = character->id.c_str()[0];
				auto it = data.fontmap.insert(std::make_pair(id, character));
				if( !it.second ){
					debug->e("[GameDataLoader] Failed to insert fontcharacter. Char:" + std::to_string(id) + " ID: " + character->id);
				}
			}
		}
	}
}