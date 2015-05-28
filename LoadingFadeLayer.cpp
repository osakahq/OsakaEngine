 #include "stdafx.h"

#include "Debug.h"
#include "EventHandler.h"
#include "EventArgs.h"
#include "ESceneArgs.h"

#include "RPGScene.h"
#include "RPGLoadingScene.h"
#include "RPGApplication.h"
#include "Canvas.h"
#include "LoadingFadeCanvas.h"
#include "Layer.h"
#include "LoadingFadeLayer.h"
#include "osaka_forward.h"

#define LOADINGSCRIPT_MIDANIMATION 116260
#define LOADINGSCRIPT_ENDANIMATION 976838

namespace Osaka{
	namespace RPGLib{
		LoadingFadeLayer::LoadingFadeLayer(std::string id, RPGApplicationPTR& app, RPGLoadingScenePTR& parent, LoadingFadeCanvasPTR& canvas, UserInterfacePTR& ui)
			: Layer(id, app, std::static_pointer_cast<RPGScene>(parent), std::static_pointer_cast<Canvas>(canvas), ui){
			
			ResetVariables();
			lcanvas = canvas;
			lparent = parent;
		}
		LoadingFadeLayer::~LoadingFadeLayer(){
#ifdef _DEBUG
			_CHECKDELETE("LoadingFadeLayer");
#endif
		}
		void LoadingFadeLayer::_delete(){
			Layer::_delete();

			lcanvas->endAnimation->Unhook(LOADINGSCRIPT_ENDANIMATION);
			lcanvas->midAnimation->Unhook(LOADINGSCRIPT_MIDANIMATION);

			scene_params = nullptr;
			lcanvas = nullptr;
			lparent = nullptr;
		}

		void LoadingFadeLayer::Init(){
			//If transitiontype == Stack, there is no endAnimation.
			lcanvas->endAnimation->Hook(LOADINGSCRIPT_ENDANIMATION, std::bind(&LoadingFadeLayer::OnCanvasEndAnimation, this, std::placeholders::_1));
			lcanvas->midAnimation->Hook(LOADINGSCRIPT_MIDANIMATION, std::bind(&LoadingFadeLayer::OnCanvasMidAnimation, this, std::placeholders::_1));
		}

		void LoadingFadeLayer::ResetVariables(){
			scene_id = "";
			scene_params = nullptr;
			loadCompleted = false;
			startAnimation = false;
		}

		void LoadingFadeLayer::OnCanvasEndAnimation(Component::EventArgs& e){
			app->debug->l("[LoadingFadeLayer] OnCanvasEndAnimation (Switch)");
			//If transitiontype == Stack, there is no endAnimation.
			app->Remove(lparent->GetId().c_str());

			ResetVariables();
		}
		void LoadingFadeLayer::OnCanvasMidAnimation(Component::EventArgs& e){
			if( transition_type == TransitionType::FADE_STACK ){
				app->debug->l("[LoadingFadeLayer] OnCanvasMidAnimation::Stack");
				//If it is stack then, there is no fade out animation
				app->Stack(scene_id.c_str(), scene_params);
				/* It has to be in this order because if there is an scene below this one, it will `Focus()` then immediately `StandBy()` */
				app->Remove(lparent->GetId().c_str());

				ResetVariables();
			}else if( transition_type == TransitionType::FADE_SWITCH ){
				app->debug->l("[LoadingFadeLayer] OnCanvasMidAnimation::Switch");
				/* Remove all scenes except this one */
				app->RemoveAllFromStack(lparent->GetId().c_str());
				app->BottomStack(scene_id.c_str(), scene_params);
			}else if( transition_type == TransitionType::LOADING_STACK){
				app->debug->e("[LoadingFadeLayer] LOADING_STACK NOT IMPLEMENTED YET");
			}
		}
		
		void LoadingFadeLayer::Ready(LayerArgsPTR& args){
			LoadingFadeLayerArgsPTR largs = std::dynamic_pointer_cast<LoadingFadeLayerArgs>(args);
			this->scene_id = largs->scene_id;
			this->scene_params = largs->scene_params;
			this->transition_type = largs->type;
			startAnimation = true;
		}

		void LoadingFadeLayer::UpdateEx(){
			if( startAnimation ){
				lcanvas->StartAnimation(transition_type);
				startAnimation = false;
			} else if( !loadCompleted && lparent->isLoadCompleted() ){
				loadCompleted = true;
				lcanvas->BeginEndAnimation();
			}
		}

	}
}