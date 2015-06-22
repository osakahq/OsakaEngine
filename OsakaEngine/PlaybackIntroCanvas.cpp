 #include "stdafx.h"
#include "GameDataParams.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Debug.h"
#include "Timer.h"
#include "EventArgs.h"
#include "EventHandler.h"
#include "Image.h"
#include "Square.h"
#include "Canvas.h"
#include "Utils.h"
#include "PlaybackIntroSceneScript.h"
#include "FadeInOutScript.h"
#include "Registree.h"
#include "RPGScene.h"
#include "Factory.h"
#include "RPGFactory.h"
#include "PlaybackIntroCanvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		PlaybackIntroCanvas::PlaybackIntroCanvas(SDL_Renderer* raw_renderer, Ruler* ruler) 
			: Canvas(raw_renderer, ruler)
		{
			this->engine_logo = NULL;
			this->gamestudio_logo = NULL;
			background = NULL;
			phase = 0;

			args = new FadeInOutLayerArgs();
			registree->Register(args->callbackOnMidAnimation, std::bind(&PlaybackIntroCanvas::CallbackLayerMidAnimation, this, std::placeholders::_1));
			registree->Register(args->callbackOnEndAnimation, std::bind(&PlaybackIntroCanvas::CallbackLayerEndAnimation, this, std::placeholders::_1));
			args->removeItselfWhenFinished = true;
		}
		PlaybackIntroCanvas::~PlaybackIntroCanvas(){
			args->callbackOnEndAnimation = nullptr;
			args->callbackOnMidAnimation = nullptr;
			delete args; args = NULL;
			
			mainscript = NULL;
			//timer, background, engine_logo, gamestudio_logo are deleted in Unload. 
			//And unload will be always be called when exiting the application
		}
		void PlaybackIntroCanvas::Init(Layer* layer_parent, RPGScene* scene_parent, Script* script, SceneScript* mainscript){
			Canvas::Init(layer_parent, scene_parent);
			//For now we don't need script, so we ignore it.
			this->mainscript = dynamic_cast<PlaybackIntroSceneScript*>(mainscript);
		}
		void PlaybackIntroCanvas::Load(RPGFactory& factory){
			timer = factory.factory->CreateTimer();
			//This will only called once because of the asset_loading_type (and the fact that there is no implementation of unload)
			background = factory.CreateSquare(ruler->x_top_left_corner, ruler->y_top_left_corner, ruler->max_height, ruler->max_width);
			background->rgba.r = background->rgba.g = background->rgba.b = 0;

			engine_logo = factory.CreateImage(factory.gamedataparams->engine_logo);
			gamestudio_logo = factory.CreateImage(factory.gamedataparams->gamestudio_logo);
		}
		void PlaybackIntroCanvas::Unload(){
			//Just an example. This function will never be called inside the loop (for now)
			//But it will be called when exiting the application (if the scene was loaded)
			delete background; background = NULL;
			delete engine_logo; engine_logo = NULL;
			delete gamestudio_logo; gamestudio_logo = NULL;
			delete timer; timer = NULL;
		}

		void PlaybackIntroCanvas::Enter(){
			phase = 0;
			movePhaseUp = false;
			timer->Start();
		}
		void PlaybackIntroCanvas::CallbackLayerMidAnimation(Component::EventArgs& e){
			switch(phase){
			case 0:
				//FadeLayer is in total black. Time to start drawing the engine logo
				movePhaseUp = true;
				//FadeInOutLayer automatically starts the end animation.
				break;
			case 1:
				movePhaseUp = true;
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			}
		}
		void PlaybackIntroCanvas::CallbackLayerEndAnimation(Component::EventArgs& e){
			
		}
		void PlaybackIntroCanvas::Update(Engine::keyboard_state& state){
			//See in header why, this is needed.
			if( movePhaseUp ){
				++phase;
				if( phase == 1 ){
					timer->Start();
				}
				movePhaseUp = false;
			}
			background->Update();
			switch(phase){
			case 0:
				if( timer->GetTicks() >= 2000 ){
					args->stillTime = 0;
					args->fadeInTime = args->fadeOutTime = 2500;
					scene_parent->Stack(mainscript->fadelayer_id, *args);
					timer->Stop();
				}
				break;
			case 1:
				if( timer->GetTicks() >= 3500 ){
					args->stillTime = 800;
					args->fadeInTime = args->fadeOutTime = 2500;
					scene_parent->Stack(mainscript->fadelayer_id, *args);
					timer->Stop();
				}
				engine_logo->Update();
				break;
			case 2:
				gamestudio_logo->Update();
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			}
			
			//engine_logo->Update();
		}
		void PlaybackIntroCanvas::Draw(){
			background->Draw();
			switch(phase){
			case 1:
				engine_logo->Draw();
				break;
			case 2:
				gamestudio_logo->Draw();
				break;
			}
		}
	}
}