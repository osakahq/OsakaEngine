 #include "stdafx.h"
#include "EventHandler.h"
#include "EventArgs.h"
#include "Debug.h"
#include "LoadingCanvas.h"
#include "LoadingUI.h"
#include "ESceneArgs.h"
#include "LoadingArgs.h"
#include "RPGLoadingScene.h"
#include "RPGApplication.h"
#include "Script.h"
#include "LoadingScript.h"
#include "osaka_forward.h"

#define LOADINGSCRIPT_MIDANIMATION 116260
#define LOADINGSCRIPT_ENDANIMATION 976838


namespace Osaka{
	namespace RPGLib{
		LoadingScript::LoadingScript(RPGApplicationPTR& app) : Script(app){
			ResetVariables();
			canvas = nullptr;
			ui = nullptr;
		}
		LoadingScript::~LoadingScript(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingScript");
#endif
		}
		void LoadingScript::_delete(){
			Script::_delete();
			loadingparent = nullptr;

			canvas->endAnimation->Unhook(LOADINGSCRIPT_ENDANIMATION);
			canvas->midAnimation->Unhook(LOADINGSCRIPT_MIDANIMATION);
			canvas = nullptr;
			ui = nullptr;

			scene_params = nullptr;
		}
		
		void LoadingScript::Init(RPGLoadingScenePTR& parent, LoadingCanvasPTR& canvas, LoadingUIPTR& ui){
			Script::Init(std::static_pointer_cast<RPGScene>(parent));

			loadingparent = parent;
			this->canvas = canvas;
			this->ui = ui;
			//If transitiontype == Stack, there is no endAnimation.
			canvas->endAnimation->Hook(LOADINGSCRIPT_ENDANIMATION, std::bind(&LoadingScript::OnCanvasEndAnimation, this, std::placeholders::_1));
			canvas->midAnimation->Hook(LOADINGSCRIPT_MIDANIMATION, std::bind(&LoadingScript::OnCanvasMidAnimation, this, std::placeholders::_1));
		}
		void LoadingScript::ResetVariables(){
			scene_id = "";
			scene_params = nullptr;
			loadCompleted = false;
		}

		void LoadingScript::OnCanvasEndAnimation(Component::EventArgs& e){
			app->debug->l("[LoadingScript] OnCanvasEndAnimation (Switch)");
			//If transitiontype == Stack, there is no endAnimation.
			app->Remove(loadingparent->GetId().c_str());

			ResetVariables();
		}
		void LoadingScript::OnCanvasMidAnimation(Component::EventArgs& e){
			if( transition_type == TransitionType::FADE_STACK ){
				app->debug->l("[LoadingScript] OnCanvasMidAnimation::Stack");
				//If it is stack then, there is no fade out animation
				app->Stack(scene_id.c_str(), scene_params);
				/* It has to be in this order because if there is an scene below this one, it will `Focus()` then immediately `StandBy()` */
				app->Remove(loadingparent->GetId().c_str());

				ResetVariables();
			}else if( transition_type == TransitionType::FADE_SWITCH ){
				app->debug->l("[LoadingScript] OnCanvasMidAnimation::Switch");
				/* Remove all scenes except this one */
				app->RemoveAllFromStack(loadingparent->GetId().c_str());
				app->BottomStack(scene_id.c_str(), scene_params);
			}else if( transition_type == TransitionType::LOADING_STACK){
				app->debug->e("[LoadingScript] LOADING_STACK NOT IMPLEMENTED YET");
			}
		}
		
		void LoadingScript::Ready(Engine::ESceneArgsPTR& params){
			LoadingArgsPTR lparams = std::dynamic_pointer_cast<LoadingArgs>(params);
			scene_id = lparams->scene;
			scene_params = lparams->send_params;
			transition_type = lparams->type;
			canvas->StartAnimation(lparams->type);
		}

		void LoadingScript::Exit(){
			app->debug->l("[LoadingScript] Hide");
		}
		
		void LoadingScript::Update(){
			if( !loadCompleted && loadingparent->isLoadCompleted() ){
				loadCompleted = true;
				canvas->BeginEndAnimation();
			}
		}
		
	}
}