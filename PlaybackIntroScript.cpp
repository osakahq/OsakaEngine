 #include "stdafx.h"
#include "AssetManager.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "engine_include.h"

#include "EventHandler.h"
#include "EventArgs.h"
#include "Debug.h"
#include "PlaybackIntroCanvas.h"
#include "PlaybackIntroUI.h"
#include "EScenePassParams.h"
#include "RPGApplication.h"
#include "Script.h"
#include "PlaybackIntroScript.h"
#include "osaka_forward.h"

#define MYTEXT_TEST1 "593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 890 mf ddfXX593458938 98j7 897 87 89789 7 8ENDENDENDXX"
#define MYTEXT_TEST2 "font_A"

namespace Osaka{
	namespace RPGLib{
		PlaybackIntroScript::PlaybackIntroScript(RPGApplicationPTR& app) : Script(app){
			
		}
		PlaybackIntroScript::~PlaybackIntroScript(){

		}
		void PlaybackIntroScript::_delete(){
			Script::_delete();
			
			canvas = nullptr;
			ui = nullptr;
		}
		
		void PlaybackIntroScript::Init(PlaybackIntroCanvasPTR& canvas, PlaybackIntroUIPTR& ui){
			this->canvas = canvas;
			this->ui = ui;
		}
		
		void PlaybackIntroScript::Load(){
			//There is nothing to load because LoadingScene assets HAVE to be in init-load assets (XML)
		}
		void PlaybackIntroScript::Unload(){
		}
		void PlaybackIntroScript::Show(Engine::EScenePassParamsPTR& params){
			
		}

		void PlaybackIntroScript::Hide(){
		}
		void PlaybackIntroScript::StandBy(){
		}
		void PlaybackIntroScript::StandBy(Engine::EScenePassParamsPTR& params){
			
		}
		void PlaybackIntroScript::Focus(){
			app->debug->l("[PlaybackIntroScript] Focus");
		}
		void PlaybackIntroScript::Update(){
			
		}
		void PlaybackIntroScript::Draw(){
			
			//11-12ms per frame
			//app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);

			//11-12ms per frame
			/*Engine::render_info info(5, 35, 0, NULL, SDL_FLIP_NONE);
			for(int i = 0; i < 988; ++i){
				app->assetm->texturem->RenderSprite(MYTEXT_TEST2, info);
				
				info.x += 12;
				if( info.x >= 504 ){
					info.x = 5;
					info.y += 14;
				}
			}*/
		}
		void PlaybackIntroScript::Reset(){
		}
	}
}