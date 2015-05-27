 #include "stdafx.h"
#include "RPGScene.h"
#include "RPGApplication.h"
#include "Canvas.h"
#include "UserInterface.h"
#include "Layer.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		Layer::Layer(std::string id, RPGApplicationPTR& app, RPGScenePTR& parent, CanvasPTR& canvas, UserInterfacePTR& ui){
			this->id = id;
			this->app = app;
			this->parent = parent;

			this->canvas = canvas;
			this->ui = ui;

			focus = false;
			instack = false;
			standby = false;
			hidden = false;
		}
		Layer::~Layer(){
	
		}
		void Layer::_delete(){
			//The order in which they are deleted matters.
			canvas->_delete(); canvas = nullptr;
			ui->_delete(); ui = nullptr;

			app = nullptr;
			parent = nullptr;
		}

		/* These functions are not required to be implemented in the derived classes */
		void Layer::Load(){
			canvas->Load();
			ui->Load();
		}
		void Layer::Unload(){
			canvas->Unload();
			ui->Unload();
		}
		void Layer::Ready(){
			instack = true;

			canvas->Ready();
			ui->Ready();
		}
		void Layer::Exit(){
			instack = false;

			canvas->Exit();
			ui->Exit();
		}

		void Layer::Show(){
			focus = true;
			standby = false;
			hidden = false;

			canvas->Show();
			ui->Show();
		}
		void Layer::StandBy(){
			focus = false;
			standby = true;
			hidden = false;

			canvas->StandBy();
			ui->StandBy();
		}
		void Layer::Focus(){
			focus = true;
			standby = false;

			canvas->Focus();
			ui->Focus();
		}

		void Layer::Update(){
			if( hidden )
				return;
			//I had to create a separate Update so I don't have to worry about always adding `if( hidden )` in the derived class.
			this->UpdateEx();
			canvas->Update();
			ui->Update();
		}
		void Layer::Draw(){
			if( hidden )
				return;
			
			canvas->Draw();
			ui->Draw();
		}
		void Layer::UpdateEx(){
			//Dummy. In case we don't need it in the derived class.
		}

		void Layer::StandByHide(bool val){
			hidden = val;
		}
	}
}