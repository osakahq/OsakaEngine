 #include "stdafx.h"
#ifndef RPGLIB_GAMEDATALOADER_H
#define RPGLIB_GAMEDATALOADER_H
#include "osaka_forward.h"
#include "rapidxml.hpp"
#define GAMEDATA_LINEFEED_WINDOWS "windows"

namespace Osaka{
	
	namespace RPGLib{
		
		/* We leverage the scene_data struct, for the groups. 
		 * Remember that a scene_data does NOT have a group struct. The group data is "copied" to the scene_data */
		typedef scene_dataPTR group_dataPTR;
		typedef std::unordered_map<std::string, scene_dataPTR> unorderedmap_group_data;

		class GameDataLoader{
		public:
			GameDataLoader(Debug::DebugPTR& debug, FactoryPTR& factory);
			~GameDataLoader();
			void _delete();
			/* The one who calls it, gets the ownership of GameData */
			GameDataPTR LoadGameFile(const char* filename);

			/* Doesn't take ownership. */
			bool SaveGame(unorderedmap_gamesession_dataPTR& gamesessions, const char* filename);
			/* Gives away ownership. Creates the structs from the files. The same thing in LoadGameFile */
			unorderedmap_gamesession_dataPTR LoadGame(const char* filename);
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner*/
			Debug::DebugPTR debug;

			/* NOT Owner*/
			FactoryPTR factory;

			void LoadInitialAssetmap(GameDataPTR& data, rapidxml::xml_node<>& init_load_node);
			void LoadAssetGroups(unorderedmap_group_data& groups, rapidxml::xml_node<>& groups_node);
			/* We need the groups so we can "copy" the data to the scene_data */
			void LoadScenesAssetmap(unorderedmap_group_data& groups, GameDataPTR& data, rapidxml::xml_node<>& scenes_node);

			void LoadSpritemaps(GameDataPTR& data, rapidxml::xml_node<>& spritemaps_node, std::string linefeed);
			void LoadSounds(GameDataPTR& data, rapidxml::xml_node<>& sounds_node);

			void LoadFontmap(GameDataPTR& data, rapidxml::xml_node<>& fontmap_node);

			void LoadBattleData(GameDataPTR& data, rapidxml::xml_node<>& node);
			void LoadCharacterData(GameDataPTR& data, rapidxml::xml_node<>& node);

			/* Helper function. It modifies the related_scene_data struct */
			void SetRelatedScene(related_scene_data* related_scene, rapidxml::xml_node<>& related_scene_node);
			/* Helper function. It modifies the scene_data struct */
			void CopyGroupData(scene_data* scene_d, const group_dataPTR& group_data);
			/* Helper function to return the adecuate Enum value for the given type */
			unsigned int GetAssetType(const char* type);
			bool GetTrueFalse(const char* text);
		};
	}
}
#endif