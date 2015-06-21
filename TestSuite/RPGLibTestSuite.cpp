 #include "stdafx.h"
#include <engine_include.h>
#include <gamedata_include.h>
#include <ESceneArgs.h>
#include <EScene.h>
#include <DummyScene.h>
#include <RPGScene.h>
#include <Debug.h>
#include <Factory.h>
#include <ServerConn.h>
#include <GameDataLoader.h>
#include <SceneFactory.h>
#include <GameSessionManager.h>
#include <RPGFactory.h>
#include <GameData.h>
#include <RPGApplication.h>
#include "TestApplicationBuilder.h"
#include "RPGLibTestSuite.h"
#include <ConsoleColors.h>
#include "_testsuite_macro.h"

namespace Osaka{
	namespace TestSuite{
		RPGLibTestSuite::RPGLibTestSuite(){
			this->debug = nullptr;
			this->rpgapp = nullptr;

			failedTests = 0;
			succesfulTests = 0;

			/* This value should be gotten from command line arguments */
			bool commandlineargs_debug = true;
			this->debug = new Debug::Debug("tests\\test-log.txt", true, Debug::DEBUG_LEVEL::CONSOLE, commandlineargs_debug);
			Network::ServerConn* conn = new Network::ServerConn(debug);
			debug->init(conn);
			rpgapp = NULL;
		}
		RPGLibTestSuite::~RPGLibTestSuite(){
			if( rpgapp != NULL ){
				delete rpgapp; rpgapp = NULL;
			}
			delete debug; debug = NULL;
		}
		
		void RPGLibTestSuite::Run(TEST_PHASE::Value phase){
			/* This has to be the same as in Ascension.cpp */
			LOG("[RPGLibTestSuite] Run\n");
			
			TestApplicationBuilder* appbuilder = new TestApplicationBuilder();

			/* To know which phase does what, refer to `testsuite_run.cpp` */
			if( phase == TEST_PHASE::PHASE1 ){
				this->rpgapp = appbuilder->Create("tests\\SceneTests_Phase1\\phase1_data.xml", "tests\\SceneTests_Phase1\\does_not_exists.xml", "tests\\SceneTests_Phase1\\does_not_exists.7z", *debug);
				
				int tests[] = {TESTID_PHASE1_PLAYBACKLOAD, TESTID_PHASE1_PLAYBACKLOAD_LINKED};
				AddExpectedTests(sizeof(tests)/sizeof(*tests), tests);
				rpgapp->AddScene("playbackintro_phase1_test1", rpgapp->scenefactory->CreatePlaybackIntroScene("playbackintro_phase1_test1"));
				rpgapp->AddScene("test_startmenu", rpgapp->scenefactory->CreateStartMenuScene("test_startmenu"));
				
				rpgapp->AddScene("loadgame", rpgapp->scenefactory->CreateDummyScene("loadgame"));
				rpgapp->AddScene("options", rpgapp->scenefactory->CreateDummyScene("options"));
				rpgapp->AddScene("credits", rpgapp->scenefactory->CreateDummyScene("credits"));
				rpgapp->AddScene("playback_newgame", rpgapp->scenefactory->CreateDummyScene("playback_newgame"));

				rpgapp->Run("playbackintro_phase1_test1", Engine::EmptyESceneArgsPTR);
			}else{
				LOG("[RPGLibTestSuite] Unkown phase.\n");
			}
			
			delete appbuilder;
		}
		void RPGLibTestSuite::MakeAssert(const bool test, const int cline, const char* cfile){
			if( test ){
				succesfulTests++;
			}else{
				failedTests++;

				std::cout << Debug::red;
				LOG("Test failed. Line: [%d] File: [%s]\n", cline, cfile);
				std::cout << Debug::white;
			}
			
		}
		void RPGLibTestSuite::MakeAssertEx(const int id, const bool test, const int cline, const char* cfile){
			auto it = expectedTests.find(id);
			if( it == expectedTests.end() ){
				debug->e("[RPGLibTestSuite] Expected result not found: "+std::to_string(id));
			}

			//For now, we can't call it more than once per ID. But if the result doesn't change, then it should be okay
			if( (it->second == ASSERTEX_SUCCESS && test == false) || (it->second == ASSERTEX_FAIL && test == true) ){
				debug->e("[RPGLibTestSuite] Test called more than once, but their results differ: "+std::to_string(id));
			}

			it->second = (test) ? ASSERTEX_SUCCESS : ASSERTEX_FAIL;
		}
		void RPGLibTestSuite::CheckResults(){
			if( expectedTests.size() > 0 ){
				int notcalled = 0;
				int success = 0;
				int fail = 0;
				MULTIPLE_LOG_START("[RPGLibTestSuite] Results (expected): \n");
				MULTIPLE_LOG_END("[RPGLibTestSuite] [F]ailed/[N]ot called tests: ");
				for( auto it = expectedTests.begin(); it != expectedTests.end(); ++it ){
					switch(it->second){
					case ASSERTEX_NOTCALLED:
						LOG("%d[n], ", it->first);
						++notcalled;
						break;
					case ASSERTEX_FAIL:
						LOG("%d[f], ", it->first);
						++fail;
						break;
					case ASSERTEX_SUCCESS:
						++success;
						break;
					default:
						debug->e("[RPGLibTestSuite] Unkown result...? What happened?");
						break;
					}
				}
				MULTIPLE_LOG_START("\n");
				MULTIPLE_LOG("\t%d not called tests.\n", notcalled);
				MULTIPLE_LOG("\t%d succesful tests.\n", success);
				MULTIPLE_LOG_END("\t%d failed tests.\n", fail);
				if( fail == 0 && notcalled == 0 ){
					std::cout << Debug::green;
					LOG("[RPGLibTestSuite] Veredict (expected): PASSED\n");
				}else{
					std::cout << Debug::red;
					LOG("[RPGLibTestSuite] Veredict (expected): FAILED\n");
				}
				std::cout << Debug::white;

				//Not be confused with the expected results
				if( succesfulTests == 0 && failedTests == 0 ){
					//If there are no normal tests, and there are expected tests, then its fine to exit function.
					return;
				}
			}
			if( succesfulTests == 0 && failedTests == 0 ){
				std::cout << Debug::yellow;
				LOG("[RPGLibTestSuite] 0 tests were conducted.\n");
				std::cout << Debug::white;
				return;
			}
			MULTIPLE_LOG_START("[RPGLibTestSuite] Results: \n");
			MULTIPLE_LOG("\t%d succesful tests.\n", succesfulTests);
			MULTIPLE_LOG_END("\t%d failed tests.\n", failedTests);
			if( failedTests == 0 ){
				std::cout << Debug::green;
				LOG("[RPGLibTestSuite] Veredict: PASSED\n");
			}else{
				std::cout << Debug::red;
				LOG("[RPGLibTestSuite] Veredict: FAILED\n");
			}
			std::cout << Debug::white;
		}
		void RPGLibTestSuite::AddExpectedTests(int size, int* array_ids){
			if( expectedTests.size() > 0 ){
				debug->e("[RPGLibTestSuite] You can only call AddExpectedTests per execution.");
			}
			for( int i = 0; i < size; ++i ){
				expectedTests[array_ids[i]] = ASSERTEX_NOTCALLED;
			}
		}

		void RPGLibTestSuite::IndividualTest_LoadGameFileTest(const char* filedata, bool verbose){
			/* Make sure to call `_delete()` and set them `nullptr` when done (data, loader) */
			GameData* data = new GameData();
			GameDataLoader* loader = new GameDataLoader(debug);
			loader->LoadGameFile(filedata, *data);

			/* Since the file is already loaded... we only need to make sure it is correctly loaded... */
			MULTIPLE_LOG_START("[TestLoadGameFile] Start\n");
			MULTIPLE_LOG_END("[TestLoadGameFile] Spritemaps count: %d\n", data->spritemaps.size());

			for( auto it = data->spritemaps.begin(); it != data->spritemaps.end(); ++it ){	
				LOG("\t ID: %s \t %d\n", it->first.c_str(), it->second->sprites.size());
				if( verbose ){
					for( auto it_sprite = it->second->sprites.begin(); it_sprite != it->second->sprites.end(); ++it_sprite ){
						LOG("\t\t %s \t X: %d, Y: %d, W: %d, H: %d \n", it_sprite->first.c_str(), it_sprite->second.clip.x, it_sprite->second.clip.y, it_sprite->second.clip.w, it_sprite->second.clip.h);
					}
				}
			}
			
			//Check values
			OSAKA_ASSERT( ( data->spritemaps.at("texturemap_common")->sprites.size() == 107 ));
			
			OSAKA_ASSERT( ( data->spritemaps.at("texturemap_cinematics")->colorkey.r == 0xFF ));
			OSAKA_ASSERT( ( data->spritemaps.at("texturemap_common")->colorkey.b == 0xFF ));
			LOG("[TestLoadGameFile] Texturemap cinematics colorkey.r = %d\n", data->spritemaps.at("texturemap_cinematics")->colorkey.r);
			sprite_data* sprite;
			sprite = &data->spritemaps.at("texturemap_cinematics")->sprites.at("startmenu_background");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 0 || sprite->clip.w != 614 || sprite->clip.h != 608 ));//0 0 614 608
			
			sprite = &data->spritemaps.at("texturemap_cinematics")->sprites.at("startmenu_subtitle");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 608 || sprite->clip.w != 496 || sprite->clip.h != 35 ));//0 608 496 35
			
			sprite = &data->spritemaps.at("texturemap_cinematics")->sprites.at("startmenu_title");
			OSAKA_ASSERT( !( sprite->clip.x != 614 || sprite->clip.y != 0 || sprite->clip.w != 400 || sprite->clip.h != 51 ));//614 0 400 51
			

			//COMMON FILE
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("focus");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 32 || sprite->clip.w != 16 || sprite->clip.h != 16 ));//0 32 16 16
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("table");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 0 || sprite->clip.w != 32 || sprite->clip.h != 32 ));//0 0 32 32
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font_Z");
			OSAKA_ASSERT( !( sprite->clip.x != 196 || sprite->clip.y != 14 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//196 14 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font_Y");
			OSAKA_ASSERT( !( sprite->clip.x != 208 || sprite->clip.y != 0 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//208 0 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font_}");
			OSAKA_ASSERT( !( sprite->clip.x != 96 || sprite->clip.y != 84 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font_} = 96 84 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font_+");
			OSAKA_ASSERT( !( sprite->clip.x != 84 || sprite->clip.y != 98 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font_+ = 84 98 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font__arrowup");
			OSAKA_ASSERT( !( sprite->clip.x != 88 || sprite->clip.y != 28 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__arrowup = 88 28 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font_@");
			OSAKA_ASSERT( !( sprite->clip.x != 64 || sprite->clip.y != 0 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font_@ = 64 0 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font_$");
			OSAKA_ASSERT( !( sprite->clip.x != 28 || sprite->clip.y != 32 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font_$ = 28 32 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font__gt");
			OSAKA_ASSERT( !( sprite->clip.x != 12 || sprite->clip.y != 90 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__gt = 12 90 12 14

			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("wood_center");
			OSAKA_ASSERT( !( sprite->clip.x != 32 || sprite->clip.y != 0 || sprite->clip.w != 32 || sprite->clip.h != 32 ));//wood_center = 32 0 32 32
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font__O2");
			OSAKA_ASSERT( !( sprite->clip.x != 60 || sprite->clip.y != 70 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__O2 = 60 70 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font__sqmark");
			OSAKA_ASSERT( !( sprite->clip.x != 60 || sprite->clip.y != 84 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__sqmark = 60 84 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font__heart");
			OSAKA_ASSERT( !( sprite->clip.x != 0 || sprite->clip.y != 104 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__heart = 0 104 12 14
			sprite = &data->spritemaps.at("texturemap_common")->sprites.at("font__B1");
			OSAKA_ASSERT( !( sprite->clip.x != 112 || sprite->clip.y != 14 || sprite->clip.w != 12 || sprite->clip.h != 14 ));//font__B1 = 112 14 12 14
			
			sound_data* sound;
			sound = data->sounds.at("s_startmenu");
			OSAKA_ASSERT(strcmp(sound->filename.c_str(), "data\\title.mid") == 0 );
			sound = data->sounds.at("s_cursor_cancel");
			OSAKA_ASSERT( sound->type == SoundType::Effect );

			OSAKA_ASSERT( data->asset_loading_type == AssetLoadingType::SMARTLOAD_PARCIAL_NOUNLOAD);
			OSAKA_ASSERT( data->assets_type.at("texturemap_common") == AssetType::TEXTURE );
			OSAKA_ASSERT( data->assets_type.at("s_cursor_move") == AssetType::SOUND );

			scene_data* scene_d;
			scene_d = data->assets_scenes.at("startmenu");
			OSAKA_ASSERT( data->assets_type.at("texturemap_cinematics") == AssetType::TEXTURE );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("loadgame").always_load == true );
			//OSAKA_ASSERT( scene_d->related_scenes_data.at("loadgame").when_switch_unload_self == false );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("playback_intro").always_load == false );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("playback_intro").linked == false );
			//OSAKA_ASSERT( scene_d->related_scenes_data.at("playback_intro").when_switch_unload_self == true );
			
			scene_d = data->assets_scenes.at("playback_intro");
			OSAKA_ASSERT( scene_d->assets.at("video_intro").always_load_unload == true );

			/* Groups */
			scene_d = data->assets_scenes.at("battle_town1");
			OSAKA_ASSERT( scene_d->assets.at("texturemap_cinematics").id == "texturemap_cinematics" );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("pause").linked == true );
			OSAKA_ASSERT( scene_d->related_scenes_data.at("battle_victory").always_load == true );

			scene_d = data->assets_scenes.at("world_earth");
			OSAKA_ASSERT( scene_d->related_scenes_data.at("charactermenu").always_load == true );
			
			scene_d = data->assets_scenes.at("instance_town1");
			OSAKA_ASSERT( scene_d->related_scenes_data.at("charactermenu").always_load == true );
			
			OSAKA_ASSERT( data->default_render_color_data.b == 0xFF );
			OSAKA_ASSERT( data->default_render_color_data.a == 0xFF );


			/* Fonts */
			OSAKA_ASSERT( strcmp(data->fontmap_error.c_str(), "?") == 0 );
			OSAKA_ASSERT( strcmp(data->fontmap.at('?')->sprite.c_str(), "font__eqmark") == 0 );
			
			delete data; data = NULL;
			delete loader; loader = NULL;
		}
	}
}