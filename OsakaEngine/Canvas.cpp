 #include "stdafx.h"
#include "SDLLib.h"
#include "Ruler.h"
#include "Layer.h"
#include "RPGScene.h"
#include "Canvas.h"
#include "Registree.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		Canvas::Canvas(SDL_Renderer* raw_renderer, Ruler* ruler){
			this->raw_renderer = raw_renderer;
			this->ruler = ruler;

			layer_parent = NULL;
			scene_parent = NULL;

			registree = Component::Registree::CreateRawRegistree();
		}
		Canvas::~Canvas(){
#ifdef _DEBUG
			_CHECKDELETE("Canvas");
#endif			
			layer_parent = NULL;
			scene_parent = NULL;
			ruler = NULL;
			raw_renderer = NULL;
			delete registree; registree = NULL;
		}
		
		void Canvas::Init(Layer* layer_parent, RPGScene* scene_parent, Script* script, SceneScript* mainscript){
			this->layer_parent = layer_parent;
			this->scene_parent = scene_parent;
		}
		void Canvas::Init(Layer* layer_parent, RPGScene* scene_parent){
			//This is the function the derived class will call if it overrides the INit(layer,scene,script,mainscript) function
			this->layer_parent = layer_parent;
			this->scene_parent = scene_parent;
		}

		/* These functions are not required to be implemented in the derived classes */
		void Canvas::Enter(){}
		void Canvas::Load(RPGFactory& factory){}
		void Canvas::Unload(){}
		void Canvas::Ready(){}
		void Canvas::Exit(){}

		void Canvas::Show(){}
		void Canvas::StandBy(){}
		void Canvas::Focus(){}

	}
}