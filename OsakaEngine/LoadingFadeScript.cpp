 #include "stdafx.h"

#include "Debug.h"
#include "EventHandler.h"
#include "Registree.h"
#include "EventArgs.h"
#include "ESceneArgs.h"

#include "Layer.h"
#include "RPGScene.h"
#include "LoadingSceneScript.h"
#include "RPGApplication.h"
#include "LoadingFadeCanvas.h"
#include "LoadingFadeScript.h"
#include "osaka_forward.h"

#define LOADINGSCRIPT_MIDANIMATION 116260
#define LOADINGSCRIPT_ENDANIMATION 976838

namespace Osaka{
	namespace RPGLib{
		LoadingFadeScript::LoadingFadeScript(RPGApplication* app, RPGScene* parent, LoadingFadeCanvas* canvas, LoadingSceneScript* mainscript)
			: Script(app, parent)
		{
			
			ResetVariables();
			lcanvas = canvas;
			this->mainscript = mainscript;
		}
		LoadingFadeScript::~LoadingFadeScript(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingFadeScript");
#endif
			scene_params = nullptr;
			lcanvas = NULL;
			mainscript = NULL;
		}
		
		void LoadingFadeScript::Init(Layer* layer_parent){
			Script::Init(layer_parent);
			//If transitiontype == Stack, there is no endAnimation.
			registree->Register(lcanvas->endAnimation, std::bind(&LoadingFadeScript::OnCanvasEndAnimation, this, std::placeholders::_1));
			registree->Register(lcanvas->midAnimation, std::bind(&LoadingFadeScript::OnCanvasMidAnimation, this, std::placeholders::_1));
		}

		void LoadingFadeScript::ResetVariables(){
			scene_id = "";
			scene_params = nullptr;
			loadCompleted = false;
			startAnimation = false;
		}

		void LoadingFadeScript::OnCanvasEndAnimation(Component::EventArgs& e){
			LOG("[LoadingFadeLayer] OnCanvasEndAnimation (Switch)\n");
			//If transitiontype == Stack, there is no endAnimation.
			app->Remove(scene_parent->GetId());

			ResetVariables();
		}
		void LoadingFadeScript::OnCanvasMidAnimation(Component::EventArgs& e){
			if( transition_type == TransitionType::FADE_STACK ){
				LOG("[LoadingFadeLayer] OnCanvasMidAnimation::Stack\n");
				//If it is stack then, there is no fade out animation
				app->Stack(scene_id, *scene_params.get());
				scene_params = nullptr;
				/* It has to be in this order because if there is an scene below this one, it will `Focus()` then immediately `StandBy()` */
				app->Remove(scene_parent->GetId());

				ResetVariables();
			}else if( transition_type == TransitionType::FADE_SWITCH ){
				LOG("[LoadingFadeLayer] OnCanvasMidAnimation::Switch\n");
				/* Remove all scenes except this one */
				app->RemoveAllFromStack(scene_parent->GetId());
				app->BottomStack(scene_id, *scene_params.get());
				scene_params = nullptr;
			}else if( transition_type == TransitionType::LOADING_STACK){
				app->debug->e("[LoadingFadeLayer] LOADING_STACK NOT IMPLEMENTED YET");
			}
		}
		
		void LoadingFadeScript::Ready(LayerArgs& args){
			ResetVariables();

			LoadingFadeLayerArgs* largs = dynamic_cast<LoadingFadeLayerArgs*>(&args);
			this->scene_id = largs->scene_id;
			this->scene_params = largs->scene_params;
			this->transition_type = largs->type;
			startAnimation = true;
		}

		void LoadingFadeScript::Update(Engine::keyboard_state& state){
			if( startAnimation ){
				lcanvas->StartAnimation(transition_type);
				startAnimation = false;
			} else if( !loadCompleted && mainscript->isLoadCompleted() ){
				loadCompleted = true;
				lcanvas->BeginEndAnimation();
			}
		}

	}
}