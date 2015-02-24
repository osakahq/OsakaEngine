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

		GameDataLoader::GameDataLoader(Debug::DebugPTR& debug, FactoryPTR& factory){
			this->debug = debug;
			this->factory = factory;
		}
		GameDataLoader::~GameDataLoader(){
#ifdef _DEBUG
			_CHECKDELETE("GameDataLoader");
#endif		
		}
		void GameDataLoader::_delete(){
			debug = nullptr;
			factory = nullptr;
		}
		GameDataPTR GameDataLoader::LoadGameFile(const char* filename){
			GameDataPTR data = factory->CreateGameData();

			rapidxml::xml_document<> doc;
			rapidxml::file<> xmlFile(filename); //Char
			doc.parse<0>(xmlFile.data());
			
			rapidxml::xml_node<>* root = doc.first_node("game");
			data->name = root->first_attribute("name")->value();
			
			data->window_width = std::stoi(std::string(root->first_attribute("width")->value()));
			data->window_height = std::stoi(std::string(root->first_attribute("height")->value()));
			
			data->vsync = GetTrueFalse(root->first_attribute("vsync")->value());
			data->time_per_frame = std::stoi(std::string(root->first_attribute("time-per-frame")->value()));

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
				data->asset_loading_type = AssetLoadingType::FULL_LOAD_STARTUP;
			}else if( strcmp(loadin_type.c_str(), "SMARTLOAD_PARCIAL_NOUNLOAD") == 0 ){
				data->asset_loading_type = AssetLoadingType::SMARTLOAD_PARCIAL_NOUNLOAD;
			}else if( strcmp(loadin_type.c_str(), "SMARTLOAD_FULL_NOUNLOAD") == 0 ){
				data->asset_loading_type = AssetLoadingType::SMARTLOAD_FULL_NOUNLOAD;
			}else if( strcmp(loadin_type.c_str(), "SMARTLOAD") == 0 ){
				data->asset_loading_type = AssetLoadingType::SMARTLOAD;
			}

			rapidxml::xml_node<>* drc_node = root->first_node("default-render-color");
			data->default_render_color_data.r = std::stoi(drc_node->first_node("r")->value());
			data->default_render_color_data.g = std::stoi(drc_node->first_node("g")->value());
			data->default_render_color_data.b = std::stoi(drc_node->first_node("b")->value());
			data->default_render_color_data.a = std::stoi(drc_node->first_node("a")->value());
			
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

			debug->l("[GameData] Loading sprites map data...");
				LoadSpritemaps(data, *root->first_node("spritemaps"), linefeed);

			debug->l("[GameData] Loading sound data...");
				LoadSounds(data, *root->first_node("sounds"));

			return data;
		}

		void GameDataLoader::LoadInitialAssetmap(GameDataPTR& data, rapidxml::xml_node<>& init_load_node){
			//Inside asset-map > init-load node
			asset_initload_dataPTR asset_data;
			for(rapidxml::xml_node<>* asset_node = init_load_node.first_node(); asset_node != NULL; asset_node = asset_node->next_sibling("asset")){
				asset_data = std::make_shared<asset_initload_data>();
				asset_data->id = asset_node->first_attribute("id")->value();
				//asset_data->type = (AssetType::Value)GameDataLoader::GetAssetType(asset_node->Attribute("type"));
				data->assets_initload->insert(std::make_pair(asset_data->id,asset_data));
			}
		}

		void GameDataLoader::LoadAssetGroups(unorderedmap_group_data& groups, rapidxml::xml_node<>& groups_node){
			//group_dataPTR = scene_dataPTR (typedef)

			//For each group in groups node
			group_dataPTR group;
			for(rapidxml::xml_node<>* group_node = groups_node.first_node(); group_node != NULL; group_node = group_node->next_sibling("group")){
				group = std::make_shared<scene_data>();
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
				groups.insert(std::make_pair(group->id, group));
			}
		}

		void GameDataLoader::LoadScenesAssetmap(unorderedmap_group_data& groups, GameDataPTR& data, rapidxml::xml_node<>& scenes_node){
			//Inside asset-map > scenes node

			//For each scene node in scenes node
			scene_dataPTR scene_d;
			for(rapidxml::xml_node<>* scene_node = scenes_node.first_node(); scene_node != NULL; scene_node = scene_node->next_sibling("scene")){
				scene_d = std::make_shared<scene_data>();
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
					CopyGroupData(scene_d.get(), groups.at(scene_node->first_attribute("group-id")->value()));
				}
				//For each group in groups node
				if( scene_node->first_node("groups") != NULL ){
					for(rapidxml::xml_node<>* group_node = scene_node->first_node("groups")->first_node("group"); group_node != NULL; group_node = group_node->next_sibling("group")
					){
						CopyGroupData(scene_d.get(), groups.at(group_node->first_attribute("id")->value()));
					}
				}

				data->assets_scenes->insert(std::make_pair(scene_d->id, scene_d));
			}

		}

		/* Helper functions: It modifies the struct scene_data */
		void GameDataLoader::CopyGroupData(scene_data* scene_d, const group_dataPTR& group_data){
			scene_d->assets.insert(group_data->assets.begin(), group_data->assets.end());
			scene_d->related_scenes_data.insert(group_data->related_scenes_data.begin(), group_data->related_scenes_data.end());
		}

		/* Helper functions: It modifies the struct */
		void GameDataLoader::SetRelatedScene(related_scene_data* related_scene, rapidxml::xml_node<>& related_scene_node){
			related_scene->id = related_scene_node.first_attribute("id")->value();
			related_scene->linked		= GetTrueFalse(related_scene_node.first_attribute("linked")->value());
			related_scene->always_load	= GetTrueFalse(related_scene_node.first_attribute("always-load")->value());

			if( related_scene_node.first_attribute("when-switch-unload-self") != NULL ){
				related_scene->when_switch_unload_self = GetTrueFalse(related_scene_node.first_attribute("when-switch-unload-self")->value());
			}

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

		void GameDataLoader::LoadSounds(GameDataPTR& data, rapidxml::xml_node<>& sounds_node){
			//Inside <sounds> node
			sound_dataPTR sound;
			for(rapidxml::xml_node<>* sound_node = sounds_node.first_node(); sound_node != NULL; sound_node = sound_node->next_sibling("sound")){
				sound = std::make_shared<sound_data>();
				sound->filename = sound_node->first_attribute("filename")->value();
				sound->id = sound_node->first_attribute("id")->value();
				if( strcmp(sound_node->first_attribute("type")->value(), "bgm") == 0 ){
					sound->type = SoundType::BGM;
				}else{
					sound->type = SoundType::Effect;
				}
				data->assets_type->insert(std::make_pair(sound->id, AssetType::SOUND));;
				data->sounds->insert(std::make_pair(sound->id, sound));
			}
		}

		void GameDataLoader::LoadSpritemaps(GameDataPTR& data, rapidxml::xml_node<>& spritemaps_node, std::string linefeed){
			//spritemaps_node = <spritemapS> node
			
			//For each child in <spritemaps> node
			spritemap_dataPTR spritemap;
			for(rapidxml::xml_node<>* spritemap_node = spritemaps_node.first_node(); spritemap_node != NULL; spritemap_node = spritemap_node->next_sibling("spritemap")){
				//We have a <spritemap> node
				
				//`spritemap` is always inserted in GameData->spritemaps
				spritemap = std::make_shared<spritemap_data>();
				spritemap->filename = spritemap_node->first_attribute("filename")->value();
				spritemap->id = spritemap_node->first_attribute("id")->value();
				spritemap->colorkey.r = std::stoi(spritemap_node->first_attribute("colorkey-r")->value());
				spritemap->colorkey.g = std::stoi(spritemap_node->first_attribute("colorkey-g")->value());
				spritemap->colorkey.b = std::stoi(spritemap_node->first_attribute("colorkey-b")->value());
				
				//We add the texture asset to the global asset list
				data->assets_type->insert(std::make_pair(spritemap->id, AssetType::TEXTURE));

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
					
					std::vector<std::string> temp_coords;
					//at(1) = 0 0 32 32
					Utils::SplitString(temp_coords, spriteinfo_text.at(1), " ");
					//We split the string by 'space' at the end we set the sprite_data
					int coord_i = -1;
					for( auto it_coords = temp_coords.begin(); it_coords != temp_coords.end(); ++it_coords ){
						switch(++coord_i){
						case 0: temp_sprite.x = stoi(*it_coords); break;
						case 1: temp_sprite.y = stoi(*it_coords); break;
						case 2: temp_sprite.w = stoi(*it_coords); break;
						case 3:
							temp_sprite.h = stoi(*it_coords);
							//This is a copy. Inserts the sprite into the spritemap
							spritemap->sprites.insert(std::make_pair(temp_sprite.id, temp_sprite));
							//Insert the id of the sprite and where it belongs (spritemap) so I can search them easily
							data->sprite_ids->insert(std::make_pair(temp_sprite.id, spritemap->id));
							break;
						}
					}
					if( coord_i != 3 ){
						//This means we didn't get 4 numbers [0 0 32 32]
						debug->e("[GameDataLoader] Corrupted spritemap data. STAGE 2");
					}
					//Inserts the spritemap into the spritemap list (spritemapS)
					data->spritemaps->insert(std::make_pair(spritemap->id, spritemap));
				}
			}//End for (no more spritemapS)
		}
	}
}