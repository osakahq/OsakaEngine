 #include "stdafx.h"
#include "SDLLib.h"
#include "Ruler.h"
#include "Layer.h"
#include "Canvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		Canvas::Canvas(SDL_Renderer* raw_renderer, RulerPTR& ruler){
			this->raw_renderer = raw_renderer;
			this->ruler = ruler;
		}
		Canvas::~Canvas(){
#ifdef _DEBUG
			_CHECKDELETE("Canvas");
#endif			
		}
		void Canvas::_delete(){
#ifdef _DEBUG
			_CHECKDELETE("Canvas_delete");
#endif
			layer_parent = nullptr;
			scene_parent = nullptr;
			ruler = nullptr;
			raw_renderer = NULL;
		}
		void Canvas::Init(LayerPTR& layer_parent, RPGScenePTR& scene_parent, ScriptPTR& script, SceneScriptPTR& mainscript){
			this->layer_parent = layer_parent;
			this->scene_parent = scene_parent;
		}
		void Canvas::Init(LayerPTR& layer_parent, RPGScenePTR& scene_parent){
			//This is the function the derived class will call if it overrides the INit(layer,scene,script,mainscript) function
			this->layer_parent = layer_parent;
			this->scene_parent = scene_parent;
		}

		/* These functions are not required to be implemented in the derived classes */
		void Canvas::Enter(){}
		void Canvas::Load(RPGFactoryPTR& factory){}
		void Canvas::Unload(){}
		void Canvas::Ready(){}
		void Canvas::Exit(){}

		void Canvas::Show(){}
		void Canvas::StandBy(){}
		void Canvas::Focus(){}

	}
}