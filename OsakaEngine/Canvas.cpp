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
			ruler = nullptr;
			raw_renderer = NULL;
		}
		void Canvas::Init(LayerPTR& layer_parent){
			this->layer_parent = layer_parent;
		}
		/* These functions are not required to be implemented in the derived classes */
		void Canvas::Enter(){}
		void Canvas::Load(){}
		void Canvas::Unload(){}
		void Canvas::Ready(){}
		void Canvas::Exit(){}

		void Canvas::Show(){}
		void Canvas::StandBy(){}
		void Canvas::Focus(){}
	}
}