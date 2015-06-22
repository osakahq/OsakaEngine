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
			__init = false;
		}
		UserInterface::~UserInterface(){
			if( !__init ){
				LOG("[UserInterface] Didn't call init");
				throw std::exception("[UserInterface] Didn't call init");
			}
			raw_renderer = NULL;
			layer_parent = NULL;
			ruler = NULL;
		}
		
		void UserInterface::Init(Layer* layer_parent){
			this->layer_parent = layer_parent;
			__init = true;
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