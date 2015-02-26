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
			
			//Debug: 11-12ms per frame
			//Release: 1ms
			//Release x10: 6.5ms~
			//RenderCopy Release x10: 3ms
			//app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);
			/*app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);
			app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);
			app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);
			app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);
			app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);
			app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);
			app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);
			app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);
			app->assetm->fontm->RenderTextMultiple(MYTEXT_TEST1,5,35,42);*/

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

			/*Engine::TexturePTR texture = app->assetm->texturem->GetTexture("texturemap_common");
			SDL_Rect clip = {148,0,12,14}; //font_a
			//3-3.9 ms... per frame. 0.5ms slower than the next one per 60 frames.
			for(int i = 0; i < 10; ++i){
				int x = 5;
				int y = 35;
				for(int i = 0; i < 988; ++i){
					texture->Render(x, y, clip);
				
					x += 12;
					if( x >= 504 ){
						x = 5;
						y += 14;
					}
				}
			}*/
			
			/*Engine::TexturePTR texture = app->assetm->texturem->GetTexture("texturemap_common");
			SDL_Texture* sdl_texture = texture->GetTexture();
			SDL_Renderer* renderer = app->sdl->renderer;
			SDL_Rect clip = {148,0,12,14}; //font_a

			//Debug: 2-3ms~
			//Release: 2ms
			for(int i = 0; i < 10; ++i){
				int x = 0;
				int y = 0;
				SDL_Rect renderQuad = {x, y, clip.w, clip.h};
				for(int i = 0; i < 988; ++i){
					SDL_RenderCopy(renderer, sdl_texture, &clip, &renderQuad);
					
					renderQuad.x += 12;
					if( renderQuad.x >= 504 ){
						renderQuad.x = 5;
						renderQuad.y += 14;
					}
				}
			}*/

			//SDL_Rect clip = {148,0,12,14}; //font_a
			//SDL_Rect renderQuad = {5, 35, clip.w, clip.h};
			//Engine::TexturePTR texture = app->assetm->texturem->GetTexture("texturemap_common");
			//sprite_info s(*texture->GetTexture(), clip, renderQuad);

			sprite_info sprite = app->assetm->texturem->CreateSprite("font_A");
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
			}
		}
		void PlaybackIntroScript::Reset(){
		}
	}
}