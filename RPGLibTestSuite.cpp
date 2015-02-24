 #include "stdafx.h"
#include "engine_include.h"
#include "gamedata_include.h"
#include "EScene.h"
#include "RPGScene.h"
#include "Debug.h"
#include "Factory.h"
#include "ServerConn.h"
#include "RPGFactory.h"
#include "GameData.h"
#include "RPGApplication.h"
#include "rpg_bootstrap.h"
#include "RPGLibTestSuite.h"
#include "ConsoleColors.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace TestSuite{
		RPGLibTestSuite::RPGLibTestSuite(){
			this->debug = nullptr;
			this->rpgapp = nullptr;

			failedTests = 0;
			succesfulTests = 0;
		}
		RPGLibTestSuite::~RPGLibTestSuite(){
			
		}
		void RPGLibTestSuite::_delete(){
			rpgapp->_delete(); rpgapp = nullptr;
			debug->_delete(); debug = nullptr;
		}
		void RPGLibTestSuite::Init(const char* datafile, const char* settingsfile){
			if( debug != nullptr )
				return;
			/* Essentially the same as Ascension.cpp but we do not set the GameSessionManager and Run. */
			this->debug = std::make_shared<Debug::Debug>("tests\\log.txt", true, Debug::DEBUG_LEVEL::CONSOLE);
			Network::ServerConnPTR conn = std::make_shared<Network::ServerConn>(debug);
			debug->init(conn);
			debug->l("[RPGLibTestSuite] ==========================================");
			this->rpgapp = rpg_bootstrap(datafile, settingsfile, debug);
		}
		void RPGLibTestSuite::RunTests(){
			this->Init("tests\\runall_ascension_data.xml", "tests\\runall_settings.xml");
			TestLoadGameFile(false);
			//Simulating a game.
			//It has to be the same as in Ascension.cpp
			rpgapp->SetGameSessionManager(rpgapp->rpgfactory->CreateGameSessionManagerFromGameData());
			//For the scenes, We have to create TestScenes

			/* Test1 (PlaybackImage) = tests AssetManager, RPGLoadingScene, PlaybackImage */
			rpgapp->AddScene("test1", std::static_pointer_cast<Engine::EScene>(rpgapp->factory->CreatePlaybackIntroScene("test1")));
			rpgapp->Run("test1");
		}
		void RPGLibTestSuite::MakeAssert(const char* test, bool passed){
			std::string str = test;
			if( passed ){
				str += " passed";
				succesfulTests++;
				//std::cout << Debug::green;
			}else{
				str += " FAILED";
				std::cout << Debug::red;
				failedTests++;

				debug->l(str);
				std::cout << Debug::white;
			}
			
		}
		void RPGLibTestSuite::End(){
			debug->l("[RPGLibTestSuite] Results: ");
			debug->l(std::string("\t") + std::to_string(succesfulTests)+" succesful tests.");
			debug->l(std::string("\t") + std::to_string(failedTests)+" failed tests.");
			if( failedTests == 0 ){
				std::cout << Debug::green;
				debug->l("[RPGLibTestSuite] Veredict: PASSED");
			}else{
				std::cout << Debug::red;
				debug->l("[RPGLibTestSuite] Veredict: FAILED");
			}
			std::cout << Debug::white;
			debug->l("[RPGLibTestSuite] End TestSuite.");
		}
		
		void RPGLibTestSuite::TestLoadGameFile(bool verbose){
			this->Init("tests\\runall_ascension_data.xml", "tests\\generic_settings.xml");
			/* Since the file is already loaded... we only need to make sure it is correctly loaded... */
			debug->l("[TestLoadGameFile] Start");
			debug->l("[TestLoadGameFile] Spritemaps count: " + std::to_string(this->rpgapp->gameData->spritemaps->size()));

			for( auto it = this->rpgapp->gameData->spritemaps->begin(); it != this->rpgapp->gameData->spritemaps->end(); ++it ){	
				debug->l(
					//std::string("\t ")+it->first+std::string(" ID: ")+it->second->id+std::string(" Filename: ")+it->second->filename+
					std::string("\t ID: ")+it->first+
					"\t Sprites count: " + std::to_string(it->second->sprites.size())
				);
				if( verbose ){
					for( auto it_sprite = it->second->sprites.begin(); it_sprite != it->second->sprites.end(); ++it_sprite ){
						debug->l(
							//std::string("\t\t ")+it_sprite->first+std::string(" : ")+it_sprite->second.id +
							std::string("\t\t ")+it_sprite->first+
							std::string(" \t X: ")+std::to_string(it_sprite->second.x)+
							std::string(", Y: ")+std::to_string(it_sprite->second.y)+
							std::string(", W: ")+std::to_string(it_sprite->second.w)+
							std::string(", H: ")+std::to_string(it_sprite->second.h)
						);
					}
				}
			}
			GameDataPTR data = this->rpgapp->gameData;

			//Check values
			MakeAssert("[TestLoadGameFile] Test #X31: ", ( this->rpgapp->gameData->spritemaps->at("texturemap_cinematics")->sprites.size() == 3 ));
			MakeAssert("[TestLoadGameFile] Test #X32: ", ( this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.size() == 107 ));
			
			MakeAssert("[TestLoadGameFile] Test #X41: ", ( this->rpgapp->gameData->spritemaps->at("texturemap_cinematics")->colorkey.r == 0xFF ));
			MakeAssert("[TestLoadGameFile] Test #X42: ", ( this->rpgapp->gameData->spritemaps->at("texturemap_common")->colorkey.b == 0xFF ));
			debug->l("[TestLoadGameFile] Texturemap cinematics colorkey.r = " + std::to_string(this->rpgapp->gameData->spritemaps->at("texturemap_cinematics")->colorkey.r));
			sprite_data* sprite;
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_cinematics")->sprites.at("startmenu_background");
			MakeAssert("[TestLoadGameFile] Test #1: ", !( sprite->x != 0 || sprite->y != 0 || sprite->w != 614 || sprite->h != 608 ));//0 0 614 608
			
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_cinematics")->sprites.at("startmenu_subtitle");
			MakeAssert("[TestLoadGameFile] Test #2: ", !( sprite->x != 0 || sprite->y != 608 || sprite->w != 496 || sprite->h != 35 ));//0 608 496 35
			
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_cinematics")->sprites.at("startmenu_title");
			MakeAssert("[TestLoadGameFile] Test #3: ", !( sprite->x != 614 || sprite->y != 0 || sprite->w != 400 || sprite->h != 51 ));//614 0 400 51
			

			//COMMON FILE
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("focus");
			MakeAssert("[TestLoadGameFile] Test #4: ", !( sprite->x != 0 || sprite->y != 32 || sprite->w != 16 || sprite->h != 16 ));//0 32 16 16
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("table");
			MakeAssert("[TestLoadGameFile] Test #5: ", !( sprite->x != 0 || sprite->y != 0 || sprite->w != 32 || sprite->h != 32 ));//0 0 32 32
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font_Z");
			MakeAssert("[TestLoadGameFile] Test #6: ", !( sprite->x != 196 || sprite->y != 14 || sprite->w != 12 || sprite->h != 14 ));//196 14 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font_Y");
			MakeAssert("[TestLoadGameFile] Test #7: ", !( sprite->x != 208 || sprite->y != 0 || sprite->w != 12 || sprite->h != 14 ));//208 0 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font_}");
			MakeAssert("[TestLoadGameFile] Test #8: ", !( sprite->x != 96 || sprite->y != 84 || sprite->w != 12 || sprite->h != 14 ));//font_} = 96 84 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font_+");
			MakeAssert("[TestLoadGameFile] Test #9: ", !( sprite->x != 84 || sprite->y != 98 || sprite->w != 12 || sprite->h != 14 ));//font_+ = 84 98 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font__arrowup");
			MakeAssert("[TestLoadGameFile] Test #10: ", !( sprite->x != 88 || sprite->y != 28 || sprite->w != 12 || sprite->h != 14 ));//font__arrowup = 88 28 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font_@");
			MakeAssert("[TestLoadGameFile] Test #11: ", !( sprite->x != 64 || sprite->y != 0 || sprite->w != 12 || sprite->h != 14 ));//font_@ = 64 0 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font_$");
			MakeAssert("[TestLoadGameFile] Test #12: ", !( sprite->x != 28 || sprite->y != 32 || sprite->w != 12 || sprite->h != 14 ));//font_$ = 28 32 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font__gt");
			MakeAssert("[TestLoadGameFile] Test #13: ", !( sprite->x != 12 || sprite->y != 90 || sprite->w != 12 || sprite->h != 14 ));//font__gt = 12 90 12 14

			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("wood_center");
			MakeAssert("[TestLoadGameFile] Test #14: ", !( sprite->x != 32 || sprite->y != 0 || sprite->w != 32 || sprite->h != 32 ));//wood_center = 32 0 32 32
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font__O2");
			MakeAssert("[TestLoadGameFile] Test #15: ", !( sprite->x != 60 || sprite->y != 70 || sprite->w != 12 || sprite->h != 14 ));//font__O2 = 60 70 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font__sqmark");
			MakeAssert("[TestLoadGameFile] Test #16: ", !( sprite->x != 60 || sprite->y != 84 || sprite->w != 12 || sprite->h != 14 ));//font__sqmark = 60 84 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font__heart");
			MakeAssert("[TestLoadGameFile] Test #17: ", !( sprite->x != 0 || sprite->y != 104 || sprite->w != 12 || sprite->h != 14 ));//font__heart = 0 104 12 14
			sprite = &this->rpgapp->gameData->spritemaps->at("texturemap_common")->sprites.at("font__B1");
			MakeAssert("[TestLoadGameFile] Test #18: ", !( sprite->x != 112 || sprite->y != 14 || sprite->w != 12 || sprite->h != 14 ));//font__B1 = 112 14 12 14
			
			sound_dataPTR sound;
			sound = this->rpgapp->gameData->sounds->at("s_startmenu");
			MakeAssert("[TestLoadGameFile] Test #19: ", strcmp(sound->filename.c_str(), "data\\title.mid") == 0 );
			sound = this->rpgapp->gameData->sounds->at("s_cursor_cancel");
			MakeAssert("[TestLoadGameFile] Test #20: ", sound->type == SoundType::Effect );

			MakeAssert("[TestLoadGameFile] Test #21", data->asset_loading_type == AssetLoadingType::SMARTLOAD_PARCIAL_NOUNLOAD);
			MakeAssert("[TestLoadGameFile] Test #22", data->assets_type->at("texturemap_common") == AssetType::TEXTURE );
			MakeAssert("[TestLoadGameFile] Test #23", data->assets_type->at("s_cursor_move") == AssetType::SOUND );

			scene_dataPTR scene_d;
			scene_d = data->assets_scenes->at("startmenu");
			MakeAssert("[TestLoadGameFile] Test #24", data->assets_type->at("texturemap_cinematics") == AssetType::TEXTURE );
			MakeAssert("[TestLoadGameFile] Test #25", scene_d->related_scenes_data.at("loadgame").always_load == true );
			//MakeAssert("[TestLoadGameFile] Test #26", scene_d->related_scenes_data.at("loadgame").when_switch_unload_self == false );
			MakeAssert("[TestLoadGameFile] Test #27", scene_d->related_scenes_data.at("playback_intro").always_load == false );
			MakeAssert("[TestLoadGameFile] Test #AM27", scene_d->related_scenes_data.at("playback_intro").linked == false );
			//MakeAssert("[TestLoadGameFile] Test #28", scene_d->related_scenes_data.at("playback_intro").when_switch_unload_self == true );
			
			scene_d = data->assets_scenes->at("playback_intro");
			MakeAssert("[TestLoadGameFile] Test #29", scene_d->assets.at("video_intro").always_load_unload == true );

			/* Groups */
			scene_d = data->assets_scenes->at("battle_town1");
			MakeAssert("[TestLoadGameFile] Test #30", scene_d->assets.at("texturemap_cinematics").id == "texturemap_cinematics" );
			MakeAssert("[TestLoadGameFile] Test #31", scene_d->related_scenes_data.at("pause").linked == true );
			MakeAssert("[TestLoadGameFile] Test #32", scene_d->related_scenes_data.at("battle_victory").always_load == true );

			scene_d = data->assets_scenes->at("world_earth");
			MakeAssert("[TestLoadGameFile] Test #33", scene_d->related_scenes_data.at("charactermenu").always_load == true );
			
			scene_d = data->assets_scenes->at("instance_town1");
			MakeAssert("[TestLoadGameFile] Test #34", scene_d->related_scenes_data.at("charactermenu").always_load == true );
			
			MakeAssert("[TestLoadGameFile] Test #35", data->default_render_color_data.b == 0xFF );
			MakeAssert("[TestLoadGameFile] Test #36", data->default_render_color_data.a == 0xFF );


			/* Fonts */
			MakeAssert("[TestLoadGameFile] Test #37", strcmp(data->fontmap_error.c_str(), "?") == 0 );
			MakeAssert("[TestLoadGameFile] Test #38", strcmp(data->fontmap->at('?')->sprite.c_str(), "font__sqmark") == 0 );

			debug->l("[TestLoadGameFile] End");
		}
	}
}