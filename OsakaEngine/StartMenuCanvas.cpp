 #include "stdafx.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Debug.h"
#include "Timer.h"
#include "EventArgs.h"
#include "EventHandler.h"
#include "Canvas.h"
#include "Utils.h"
#include "Image.h"
#include "RPGFactory.h"
#include "Factory.h"
#include "GameDataParams.h"
#include "FloatingEffect.h"
#include "FadeInEffect.h"
#include "StartMenuCanvas.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		StartMenuCanvas::StartMenuCanvas(SDL_Renderer* raw_renderer, Ruler* ruler) : Canvas(raw_renderer, ruler){
			background = NULL;
			title = NULL;
			subtitle = NULL;
		}
		StartMenuCanvas::~StartMenuCanvas(){

		}

		void StartMenuCanvas::Init(Layer* layer_parent, RPGScene* scene_parent, Script* script, SceneScript* mainscript){
			Canvas::Init(layer_parent, scene_parent);
			//For now we dont need script/mainscript
		}
		void StartMenuCanvas::Load(RPGFactory& factory){
			timer = factory.factory->CreateTimer();
			effect = factory.CreateFloatingEffect();
			fadein = factory.CreateFadeInEffect();
			fadein->Set(5000);

			background = factory.CreateImage(factory.gamedataparams->sprite_startmenu_background);
			title = factory.CreateImage(factory.gamedataparams->sprite_startmenu_title);
			subtitle = factory.CreateImage(factory.gamedataparams->sprite_startmenu_subtitle);

			title->quad.x = ruler->MidX(title->quad.w);
			title->quad.y = ruler->MidY(title->quad.h);
			//To get 22: ((title.h + subtitle.h) / 2) / 2 = 22
			title->quad.y -= 18;
			title->quad.y -= 85;

			subtitle->quad.x = ruler->MidX(subtitle->quad.w);
			subtitle->quad.y = ruler->MidY(subtitle->quad.h);
			subtitle->quad.y += 20;
			subtitle->quad.y -= 85;

			title->AddMod(effect, DrawableModFloatingArgs(5));
			title->AddMod(fadein);
			subtitle->AddMod(fadein);
		}
		void StartMenuCanvas::Unload(){
			delete background; delete title; delete subtitle;
			background = NULL; title = NULL; subtitle = NULL;
			delete effect; effect = NULL;
			delete timer; timer = NULL;
			delete fadein; fadein = NULL;
		}
		void StartMenuCanvas::Enter(){
			
		}
		void StartMenuCanvas::Ready(){
			added_subtitle_effect = false;
			effect->Restart();
			fadein->Restart();
			//Not really needed to reset background, title, subtitle
			timer->Start();
		}
		
		void StartMenuCanvas::Update(Engine::keyboard_state& state){
			if( !added_subtitle_effect && timer->GetTicks() >= 700 ){
				added_subtitle_effect = true;
				subtitle->AddMod(effect, DrawableModFloatingArgs(7));
				timer->Stop();
			}
			fadein->Update();
			effect->Update();
			background->Update();
			title->Update();
			subtitle->Update();
		}
		void StartMenuCanvas::Draw(){
			background->Draw();
			title->Draw();
			subtitle->Draw();
		}
	}
}