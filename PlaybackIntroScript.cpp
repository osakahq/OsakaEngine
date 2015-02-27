 #include "stdafx.h"
#include "Texture.h"
#include "AssetManager.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "SDLLib.h"
#include "engine_include.h"

#include "EventHandler.h"
#include "EventArgs.h"
#include "Debug.h"
#include "PlaybackIntroCanvas.h"
#include "PlaybackIntroUI.h"
#include "ESceneArgs.h"
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
		void PlaybackIntroScript::Show(Engine::ESceneArgsPTR& params){
			
		}

		void PlaybackIntroScript::Hide(){
		}
		void PlaybackIntroScript::StandBy(){
		}
		void PlaybackIntroScript::StandBy(Engine::ESceneArgsPTR& params){
			
		}
		void PlaybackIntroScript::Focus(){
			app->debug->l("[PlaybackIntroScript] Focus");
		}
		void PlaybackIntroScript::Update(){
			
		}
		void PlaybackIntroScript::Draw(){
			
			/*sprite_info sprite = app->assetm->texturem->CreateSprite("font_A");
			sprite.quad.x = 5;
			sprite.quad.y = 35;
			for(int i = 0; i < 5; ++i){
				for(int i = 0; i < 988; ++i){
					SDL_RenderCopy(raw_renderer, sprite.raw_texture, &sprite.clip, &sprite.quad);
					
					sprite.quad.x += 12;
					if( sprite.quad.x >= 504 ){
						sprite.quad.x = 5;
						sprite.quad.y += 14;
					}
				}
			}*/
		}
		void PlaybackIntroScript::Reset(){
		}
	}
}