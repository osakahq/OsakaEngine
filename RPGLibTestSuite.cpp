 #include "stdafx.h"
#include "engine_include.h"
#include "gamedata_include.h"
#include "EScene.h"
#include "RPGScene.h"
#include "Debug.h"
#include "Factory.h"
#include "ServerConn.h"
#include "GameDataLoader.h"
#include "RPGFactory.h"
#include "GameData.h"
#include "RPGApplication.h"
#include "rpg_bootstrap.h"
#include "ApplicationCreator.h"
#include "RPGLibTestSuite.h"
#include "ConsoleColors.h"
#include "_testsuite_macro.h"

#include "osaka_forward.h"

namespace Osaka{
	namespace TestSuite{
		RPGLibTestSuite::RPGLibTestSuite(){
			this->debug = nullptr;
			this->rpgapp = nullptr;

			failedTests = 0;
			succesfulTests = 0;

			this->debug = std::make_shared<Debug::Debug>("tests\\test-log.txt", true, Debug::DEBUG_LEVEL::CONSOLE);
			Network::ServerConnPTR conn = std::make_shared<Network::ServerConn>(debug);
			debug->init(conn);
		}
		RPGLibTestSuite::~RPGLibTestSuite(){
			
		}
		void RPGLibTestSuite::_delete(){
			if( rpgapp != nullptr ){
				rpgapp->_delete(); 
				rpgapp = nullptr;
			}
			debug->_delete(); debug = nullptr;
		}
		
		void RPGLibTestSuite::Run(const char* scene){
			/* This has to be the same as in Ascension.cpp */
			debug->l("[RPGLibTestSuite] Run");
			
			Utils::ApplicationCreatorPTR appcreator = std::make_shared<Utils::ApplicationCreator>();

			this->rpgapp = rpg_bootstrap("tests\\runall_ascension_data.xml", "tests\\generic_settings.xml", "tests\\pack_file.7z", debug, appcreator);
			appcreator = nullptr;
			
			rpgapp->SetGameSessionManager(rpgapp->rpgfactory->CreateGameSessionManagerFromGameData());
			
			/* Test1 (PlaybackImage) = tests AssetManager, RPGLoadingScene, PlaybackImage */
			rpgapp->AddScene("test1", std::static_pointer_cast<Engine::EScene>(rpgapp->factory->CreatePlaybackIntroScene("test1")));
			rpgapp->Run(scene);
		}
		void RPGLibTestSuite::MakeAssert(const bool test, const int cline, const char* cfile){
			if( test ){
				succesfulTests++;
			}else{
				failedTests++;

				std::string text = "Test failed. Line: [";
				text += std::to_string(cline);
				text += "] File: [";
				text += cfile;

				std::cout << Debug::red;
				debug->l(text);
				std::cout << Debug::white;
			}
			
		}
		void RPGLibTestSuite::CheckResults(){
			if( succesfulTests == 0 && failedTests == 0 ){
				std::cout << Debug::yellow;
				debug->l("[RPGLibTestSuite] 0 tests were conducted.");
				std::cout << Debug::white;
				return;
			}
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
		
		void RPGLibTestSuite::IndividualTest_LoadGameFileTest(const char* filedata, bool verbose){
			/* Make sure to call `_delete()` and set them `nullptr` when done (data, loader) */
			GameDataPTR data = std::make_shared<GameData>();
			GameDataLoaderPTR loader = std::make_shared<GameDataLoader>(debug);
			loader->LoadGameFile(filedata, data);

			/* Since the file is already loaded... we only need to make sure it is correctly loaded... */
			debug->l("[TestLoadGameFile] Start");
			debug->l("[TestLoadGameFile] Spritemaps count: " + std::to_string(data->spritemaps->size()));

			for( auto it = data->spritemaps->begin(); it != data->spritemaps->end(); ++it ){	
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
							std::string(" \t X: ")+std::to_string(it_sprite->second.clip.x)+
							std::string(", Y: ")+std::to_string(it_sprite->second.clip.y)+
							std::string(", W: ")+std::to_string(it_sprite->second.clip.w)+
							std::string(", H: ")+std::to_string(it_sprite->second.clip.h)
						);
					}
				}
			}
			
			//Check values
			OSAKA_ASSERT( ( data->spritemaps->at("texturemap_common")->sprites.size() == 107 ));
			
			OSAKA_ASSERT( ( data->spritemaps->at("texturemap_cinematics")->colorkey.r == 0xFF ));
			OSAKA_ASSERT( ( data->spritemaps->at("texturemap_common")->colorkey.b == 0xFF ));
			debug->l("[TestLoadGameFile] Texturemap cinematics colorkey.r = " + std::to_string(data->spritemaps->at("texturemap_cinematics")->colorkey.r));
			sprite_data* sprite;
			sprite = &data->spritemaps->at("texturemap_cinematics")->sprites.at("startmenu_background");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 0 || sprite->clip.w != 614 || sprite->clip.h != 608 ));//0 0 614 608
			
			sprite = &data->spritemaps->at("texturemap_cinematics")->sprites.at("startmenu_subtitle");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 608 || sprite->clip.w != 496 || sprite->clip.h != 35 ));//0 608 496 35
			
			sprite = &data->spritemaps->at("texturemap_cinematics")->sprites.at("startmenu_title");
			OSAKA_ASSERT( !( sprite->clip.x != 614 || sprite->clip.y != 0 || sprite->clip.w != 400 || sprite->clip.h != 51 ));//614 0 400 51
			

			//COMMON FILE
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("focus");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 32 || sprite->clip.w != 16 || sprite->clip.h != 16 ));//0 32 16 16
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("table");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 0 || sprite->clip.w != 32 || sprite->clip.h != 32 ));//0 0 32 32
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font_Z");
			OSAKA_ASSERT( !( sprite->clip.x != 196 || sprite->clip.y != 14 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//196 14 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font_Y");
			OSAKA_ASSERT( !( sprite->clip.x != 208 || sprite->clip.y != 0 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//208 0 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font_}");
			OSAKA_ASSERT( !( sprite->clip.x != 96 || sprite->clip.y != 84 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font_} = 96 84 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font_+");
			OSAKA_ASSERT( !( sprite->clip.x != 84 || sprite->clip.y != 98 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font_+ = 84 98 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font__arrowup");
			OSAKA_ASSERT( !( sprite->clip.x != 88 || sprite->clip.y != 28 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__arrowup = 88 28 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font_@");
			OSAKA_ASSERT( !( sprite->clip.x != 64 || sprite->clip.y != 0 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font_@ = 64 0 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font_$");
			OSAKA_ASSERT( !( sprite->clip.x != 28 || sprite->clip.y != 32 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font_$ = 28 32 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font__gt");
			OSAKA_ASSERT( !( sprite->clip.x != 12 || sprite->clip.y != 90 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__gt = 12 90 12 14

			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("wood_center");
			OSAKA_ASSERT( !( sprite->clip.x != 32 || sprite->clip.y != 0 || sprite->clip.w != 32 || sprite->clip.h != 32 ));//wood_center = 32 0 32 32
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font__O2");
			OSAKA_ASSERT( !( sprite->clip.x != 60 || sprite->clip.y != 70 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__O2 = 60 70 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font__sqmark");
			OSAKA_ASSERT( !( sprite->clip.x != 60 || sprite->clip.y != 84 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__sqmark = 60 84 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font__heart");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 104 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__heart = 0 104 12 14
			sprite = &data->spritemaps->at("texturemap_common")->sprites.at("font__B1");
			OSAKA_ASSERT( !( sprite->clip.x != 112 || sprite->clip.y != 14 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__B1 = 112 14 12 14
			
			sound_dataPTR sound;
			sound = data->sounds->at("s_startmenu");
			OSAKA_ASSERT(strcmp(sound->filename.c_str(), "data\\title.mid") == 0 );
			sound = data->sounds->at("s_cursor_cancel");
			OSAKA_ASSERT( sound->type == SoundType::Effect );

			OSAKA_ASSERT( data->asset_loading_type == AssetLoadingType::SMARTLOAD_PARCIAL_NOUNLOAD);
			OSAKA_ASSERT( data->assets_type->at("texturemap_common") == AssetType::TEXTURE );
			OSAKA_ASSERT( data->assets_type->at("s_cursor_move") == AssetType::SOUND );

			scene_dataPTR scene_d;
			scene_d = data->assets_scenes->at("startmenu");
			OSAKA_ASSERT( data->assets_type->at("texturemap_cinematics") == AssetType::TEXTURE );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("loadgame").always_load == true );
			//OSAKA_ASSERT( scene_d->related_scenes_data.at("loadgame").when_switch_unload_self == false );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("playback_intro").always_load == false );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("playback_intro").linked == false );
			//OSAKA_ASSERT( scene_d->related_scenes_data.at("playback_intro").when_switch_unload_self == true );
			
			scene_d = data->assets_scenes->at("playback_intro");
			OSAKA_ASSERT( scene_d->assets.at("video_intro").always_load_unload == true );

			/* Groups */
			scene_d = data->assets_scenes->at("battle_town1");
			OSAKA_ASSERT( scene_d->assets.at("texturemap_cinematics").id == "texturemap_cinematics" );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("pause").linked == true );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("battle_victory").always_load == true );

			scene_d = data->assets_scenes->at("world_earth");
			OSAKA_ASSERT( scene_d->related_scenes_data.at("charactermenu").always_load == true );
			
			scene_d = data->assets_scenes->at("instance_town1");
			OSAKA_ASSERT( scene_d->related_scenes_data.at("charactermenu").always_load == true );
			
			OSAKA_ASSERT( data->default_render_color_data.b == 0xFF );
			OSAKA_ASSERT( data->default_render_color_data.a == 0xFF );


			/* Fonts */
			OSAKA_ASSERT( strcmp(data->fontmap_error.c_str(), "?") == 0 );
			OSAKA_ASSERT( strcmp(data->fontmap->at('?')->sprite.c_str(), "font__eqmark") == 0 );
			
			data->_delete(); data = nullptr;
			loader->_delete(); loader = nullptr;
		}
	}
}