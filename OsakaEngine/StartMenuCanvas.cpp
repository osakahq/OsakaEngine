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
#include "rpglib_include.h"
#include "Square.h"
#include "StartMenuCanvas.h"
#include "Registree.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		StartMenuCanvas::StartMenuCanvas(SDL_Renderer* raw_renderer, Ruler* ruler) : Canvas(raw_renderer, ruler){
			background = NULL;
			title = NULL;
			subtitle = NULL;

			phase = 0;
		}
		StartMenuCanvas::~StartMenuCanvas(){

		}

		void StartMenuCanvas::Init(Layer* layer_parent, RPGScene* scene_parent, Script* script, SceneScript* mainscript){
			Canvas::Init(layer_parent, scene_parent);
			//For now we dont need script/mainscript
		}
		void StartMenuCanvas::Load(RPGFactory& factory){
			white_background = factory.CreateSquare(ruler->x_top_left_corner, ruler->y_top_left_corner, ruler->max_height, ruler->max_width);
			white_background->rgba = Engine::RGBA(255,255,255,255);

			timer = factory.factory->CreateTimer();

			effect = factory.CreateFloatingEffect();
			effect->SetRepetitions(0, true);

			fadein = factory.CreateFadeInEffect();
			registree->Register(fadein->oneLoop, std::bind(&StartMenuCanvas::OnFadeInOneLoop, this, std::placeholders::_1));
			
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

			background->AddMod(fadein);
			fadein->Set(3000);
		}
		void StartMenuCanvas::Unload(){
			delete background; delete title; delete subtitle;
			background = NULL; title = NULL; subtitle = NULL;
			delete effect; effect = NULL;
			delete timer; timer = NULL;
			delete fadein; fadein = NULL;
			delete white_background; white_background = NULL;
		}
		void StartMenuCanvas::Enter(){
			
		}
		void StartMenuCanvas::Ready(){
			phase = 0;
			effect->Restart();
			fadein->Restart();
			//Not really needed to reset background, title, subtitle
		}
		

		void StartMenuCanvas::OnFadeInOneLoop(Component::EventArgs& e){
			switch(phase){
			case 0:
				//When this is called, fadein deattached itself so don't worry about that. You can also check in ModifierEventArgs
				fadein->Set(3500);
				fadein->Restart();
				title->AddMod(effect, DrawableModFloatingArgs(8, 0.20f));
				title->AddMod(fadein);
				
				++phase;
				break;
			case 1:
				//fadein title effect ended.
				fadein->Set(2000);
				fadein->Restart();
				subtitle->AddMod(fadein);
				subtitle->AddMod(effect, DrawableModFloatingArgs(8, 0.20f));
				//timer->Start();
				++phase;
				break;
			}
		}
		void StartMenuCanvas::Update(Engine::keyboard_state& state){
			white_background->Update();
			
			fadein->Update();
			effect->Update();

			background->Update();
			switch(phase){
			case 1:
				title->Update();
				break;
			case 2:
				title->Update();
				subtitle->Update();
				break;
			}
		}
		void StartMenuCanvas::Draw(){
			white_background->Draw();

			background->Draw();
			switch(phase){
			case 1:
				title->Draw();
				break;
			case 2:
				title->Draw();
				subtitle->Draw();
				break;
			}
		}
	}
}