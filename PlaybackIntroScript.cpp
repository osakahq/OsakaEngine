 #include "stdafx.h"
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
			
		}
		void PlaybackIntroScript::Reset(){
		}
	}
}