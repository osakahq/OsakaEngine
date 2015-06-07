 #include "stdafx.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Layer.h"
#include "UserInterface.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		UserInterface::UserInterface(SDL_Renderer* raw_renderer, RulerPTR& ruler){
			this->raw_renderer = raw_renderer;
			this->ruler = ruler;
		}
		UserInterface::~UserInterface(){
#ifdef _DEBUG
			_CHECKDELETE("UserInterface");
#endif
		}
		void UserInterface::_delete(){
#ifdef _DEBUG
			_CHECKDELETE("UserInterface_delete");
#endif
			raw_renderer = NULL;
			layer_parent = nullptr;
			ruler = nullptr;
		}

		void UserInterface::Init(LayerPTR& layer_parent){
			this->layer_parent = layer_parent;
		}

		/* These functions are not required to be implemented in the derived classes */
		void UserInterface::Enter(){}
		void UserInterface::Load(){}
		void UserInterface::Unload(){}
		void UserInterface::Ready(){}
		void UserInterface::Exit(){}

		void UserInterface::Show(){}
		void UserInterface::StandBy(){}
		void UserInterface::Focus(){}

		void UserInterface::Update(){}
		void UserInterface::Draw(){}
	}
}