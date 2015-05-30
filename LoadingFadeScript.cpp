 #include "stdafx.h"

#include "Debug.h"
#include "EventHandler.h"
#include "EventArgs.h"
#include "ESceneArgs.h"

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
		LoadingFadeScript::LoadingFadeScript(RPGApplicationPTR& app, RPGScenePTR& parent, LoadingFadeCanvasPTR& canvas, LoadingSceneScriptPTR& mainscript)
			: Script(app, parent){
			
			ResetVariables();
			lcanvas = canvas;
			this->mainscript = mainscript;
		}
		LoadingFadeScript::~LoadingFadeScript(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingFadeScript");
#endif
		}
		void LoadingFadeScript::_delete(){
			lcanvas->endAnimation->Unhook(LOADINGSCRIPT_ENDANIMATION);
			lcanvas->midAnimation->Unhook(LOADINGSCRIPT_MIDANIMATION);

			Script::_delete();
			scene_params = nullptr;
			lcanvas = nullptr;
			mainscript = nullptr;
		}

		void LoadingFadeScript::Init(LayerPTR& layer_parent){
			Script::Init(layer_parent);
			//If transitiontype == Stack, there is no endAnimation.
			lcanvas->endAnimation->Hook(LOADINGSCRIPT_ENDANIMATION, std::bind(&LoadingFadeScript::OnCanvasEndAnimation, this, std::placeholders::_1));
			lcanvas->midAnimation->Hook(LOADINGSCRIPT_MIDANIMATION, std::bind(&LoadingFadeScript::OnCanvasMidAnimation, this, std::placeholders::_1));
		}

		void LoadingFadeScript::ResetVariables(){
			scene_id = "";
			scene_params = nullptr;
			loadCompleted = false;
			startAnimation = false;
		}

		void LoadingFadeScript::OnCanvasEndAnimation(Component::EventArgs& e){
			app->debug->l("[LoadingFadeLayer] OnCanvasEndAnimation (Switch)");
			//If transitiontype == Stack, there is no endAnimation.
			app->Remove(scene_parent->GetId().c_str());

			ResetVariables();
		}
		void LoadingFadeScript::OnCanvasMidAnimation(Component::EventArgs& e){
			if( transition_type == TransitionType::FADE_STACK ){
				app->debug->l("[LoadingFadeLayer] OnCanvasMidAnimation::Stack");
				//If it is stack then, there is no fade out animation
				app->Stack(scene_id.c_str(), scene_params);
				/* It has to be in this order because if there is an scene below this one, it will `Focus()` then immediately `StandBy()` */
				app->Remove(scene_parent->GetId().c_str());

				ResetVariables();
			}else if( transition_type == TransitionType::FADE_SWITCH ){
				app->debug->l("[LoadingFadeLayer] OnCanvasMidAnimation::Switch");
				/* Remove all scenes except this one */
				app->RemoveAllFromStack(scene_parent->GetId().c_str());
				app->BottomStack(scene_id.c_str(), scene_params);
			}else if( transition_type == TransitionType::LOADING_STACK){
				app->debug->e("[LoadingFadeLayer] LOADING_STACK NOT IMPLEMENTED YET");
			}
		}
		
		void LoadingFadeScript::Ready(LayerArgsPTR& args){
			ResetVariables();

			LoadingFadeLayerArgsPTR largs = std::dynamic_pointer_cast<LoadingFadeLayerArgs>(args);
			this->scene_id = largs->scene_id;
			this->scene_params = largs->scene_params;
			this->transition_type = largs->type;
			startAnimation = true;
		}

		void LoadingFadeScript::Update(){
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