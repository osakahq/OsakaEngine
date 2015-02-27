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
#include "StaticText.h"
#include "PlaybackIntroScript.h"
#include "osaka_forward.h"

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
			
		}
		void PlaybackIntroScript::Reset(){
		}
	}
}