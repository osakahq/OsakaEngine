 #include "stdafx.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Layer.h"
#include "UserInterface.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		UserInterface::UserInterface(SDL_Renderer* raw_renderer, Ruler* ruler){
			this->raw_renderer = raw_renderer;
			this->ruler = ruler;

			layer_parent = NULL;
		}
		UserInterface::~UserInterface(){
#ifdef _DEBUG
			_CHECKDELETE("UserInterface");
#endif
			raw_renderer = NULL;
			layer_parent = NULL;
			ruler = NULL;
		}
		
		void UserInterface::Init(Layer* layer_parent){
			this->layer_parent = layer_parent;
		}

		/* These functions are not required to be implemented in the derived classes */
		void UserInterface::Enter(){}
		void UserInterface::Load(RPGFactory& factory){}
		void UserInterface::Unload(){}
		void UserInterface::Ready(){}
		void UserInterface::Exit(){}

		void UserInterface::Show(){}
		void UserInterface::StandBy(){}
		void UserInterface::Focus(){}

		void UserInterface::Update(){}
		void UserInterface::Draw(){}
		void UserInterface::End(){}
	}
}