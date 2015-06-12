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
#include "RPGScene.h"
#include "Factory.h"
#include "RPGFactory.h"
#include "PlaybackIntroCanvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		PlaybackIntroCanvas::PlaybackIntroCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler) : Canvas(raw_renderer, ruler){
			this->engine_logo = nullptr;
			this->gamestudio_logo = nullptr;
			phase = 0;

			args = std::make_shared<FadeInOutLayerArgs>();
			args->callbackOnMidAnimation = std::bind(&PlaybackIntroCanvas::CallbackLayerMidAnimation, this);
			args->callbackOnEndAnimation = std::bind(&PlaybackIntroCanvas::CallbackLayerEndAnimation, this);
			args->removeItselfWhenFinished = true;
		}
		PlaybackIntroCanvas::~PlaybackIntroCanvas(){

		}
		void PlaybackIntroCanvas::Init(LayerPTR& layer_parent, RPGScenePTR& scene_parent, ScriptPTR& script, SceneScriptPTR& mainscript){
			Canvas::Init(layer_parent, scene_parent);
			//For now we don't need script, so we ignore it.
			this->mainscript = std::dynamic_pointer_cast<PlaybackIntroSceneScript>(mainscript);
		}
		void PlaybackIntroCanvas::Load(RPGFactoryPTR& factory){
			timer = factory->factory->CreateTimer();
			//This will only called once because of the asset_loading_type (and the fact that there is no implementation of unload)
			background = factory->CreateSquare(ruler->x_top_left_corner, ruler->y_top_left_corner, ruler->max_height, ruler->max_width);
			background->rgba.r = background->rgba.g = background->rgba.b = 0;

			engine_logo = factory->CreateImage(factory->gamedataparams->engine_logo);
			gamestudio_logo = factory->CreateImage(factory->gamedataparams->gamestudio_logo);
		}
		void PlaybackIntroCanvas::Unload(){
			//Just an example. This function will never be called inside the loop (for now)
			//But it will be called when exiting the application (if the scene was loaded)
			background = nullptr;
			this->engine_logo = nullptr;
			this->gamestudio_logo = nullptr;
		}
		void PlaybackIntroCanvas::_delete(){
			/* There is not needed to set them nullptr, except Timer (for now), because when deleted, GC will set them free.
			 * You have to *always* call base::_delete though. */
			args->callbackOnEndAnimation = nullptr;
			args->callbackOnMidAnimation = nullptr;
			args = nullptr;
			timer->_delete(); timer = nullptr;
			mainscript = nullptr;
			background = nullptr;
			engine_logo = nullptr;
			gamestudio_logo = nullptr;
			Canvas::_delete();
		}
		void PlaybackIntroCanvas::Enter(){
			phase = 0;
			movePhaseUp = false;
			timer->Start();
		}
		void PlaybackIntroCanvas::CallbackLayerMidAnimation(){
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
		void PlaybackIntroCanvas::CallbackLayerEndAnimation(){
			switch(phase){
			case 0:
				break;
			case 1:
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
		void PlaybackIntroCanvas::Update(){
			//See in header why, this is needed.
			if( movePhaseUp ){
				++phase;
				if( phase == 1 ){
					timer->Start();
				}
				movePhaseUp = false;
			}
			switch(phase){
			case 0:
				if( timer->GetTicks() >= 2000 ){
					args->fadeInTime = args->fadeOutTime = 2500;
					scene_parent->Stack(mainscript->fadelayer_id, std::static_pointer_cast<LayerArgs>(args));
					timer->Stop();
				}
				background->Update();
				break;
			case 1:
				if( timer->GetTicks() >= 3500 ){
					args->fadeInTime = args->fadeOutTime = 2500;
					scene_parent->Stack(mainscript->fadelayer_id, std::static_pointer_cast<LayerArgs>(args));
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
			switch(phase){
			case 0:
				background->Draw();
				break;
			case 1:
				engine_logo->Draw();
				break;
			case 2:
				gamestudio_logo->Draw();
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			}
			//engine_logo->Draw();
		}
	}
}