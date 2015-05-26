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
		
		void PlaybackIntroScript::Init(RPGScenePTR& parent, PlaybackIntroCanvasPTR& canvas, PlaybackIntroUIPTR& ui){
			Script::Init(parent);
			this->canvas = canvas;
			this->ui = ui;
		}
		void PlaybackIntroScript::Ready(Engine::ESceneArgsPTR& params){

		}
		void PlaybackIntroScript::Focus(){
			app->debug->l("[PlaybackIntroScript] Focus");
		}
		void PlaybackIntroScript::Update(){
			
		}
	}
}