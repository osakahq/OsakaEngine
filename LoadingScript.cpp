 #include "stdafx.h"
#include "EventHandler.h"
#include "EventArgs.h"
#include "Debug.h"
#include "LoadingCanvas.h"
#include "LoadingUI.h"
#include "EScenePassParams.h"
#include "LoadingPassParams.h"
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
			parent = nullptr;

			canvas->endAnimation->Unhook(LOADINGSCRIPT_ENDANIMATION);
			/* Does not matter if mid animation was already unhooked. EventHandler does not throw an exception anymore */
			canvas->midAnimation->Unhook(LOADINGSCRIPT_MIDANIMATION);
			canvas = nullptr;
			ui = nullptr;

			scene_params = nullptr;
		}
		
		void LoadingScript::Init(RPGLoadingScenePTR& parent, LoadingCanvasPTR& canvas, LoadingUIPTR& ui){
			this->parent = parent;
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
			app->Remove(parent->id.c_str());

			ResetVariables();
		}
		void LoadingScript::OnCanvasMidAnimation(Component::EventArgs& e){
			if( transition_type == TransitionType::STACK ){
				app->debug->l("[LoadingScript] OnCanvasMidAnimation::Stack");
				//If it is stack then, there is no fade out animation
				app->Stack(scene_id.c_str(), scene_params);
				/* It has to be in this order because if there is an scene below this one, it will `Focus()` then immediately `StandBy()` */
				app->Remove(parent->id.c_str());

				ResetVariables();
			}else if( transition_type == TransitionType::SWITCH ){
				app->debug->l("[LoadingScript] OnCanvasMidAnimation::Switch");
				/* Remove all scenes except this one */
				app->RemoveAllFromStack(parent->id.c_str());
				app->BottomStack(scene_id.c_str(), scene_params);
			}
		}
		void LoadingScript::Load(){
			//There is nothing to load because LoadingScene assets HAVE to be in init-load assets (XML)
		}
		void LoadingScript::Unload(){
		}
		void LoadingScript::Show(Engine::EScenePassParamsPTR& params){
			LoadingPassParamsPTR lparams = std::dynamic_pointer_cast<LoadingPassParams>(params);
			scene_id = lparams->scene;
			scene_params = lparams->send_params;
			transition_type = lparams->type;
			canvas->StartAnimation(lparams->type);
		}

		void LoadingScript::Hide(){
			app->debug->l("[LoadingScript] Hide");
		}
		void LoadingScript::StandBy(){
		}
		void LoadingScript::StandBy(Engine::EScenePassParamsPTR& params){
			Show(params);
		}
		void LoadingScript::Focus(){
		}
		void LoadingScript::Update(){
			if( !loadCompleted && parent->isLoadCompleted() ){
				loadCompleted = true;
				canvas->BeginEndAnimation();
			}
		}
		void LoadingScript::Draw(){
			
		}
		void LoadingScript::Reset(){
		}
	}
}