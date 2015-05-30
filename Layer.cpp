 #include "stdafx.h"

#include "RPGApplication.h"
#include "Script.h"
#include "Canvas.h"
#include "UserInterface.h"
#include "Layer.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		Layer::Layer(std::string id, ScriptPTR& script, CanvasPTR& canvas, UserInterfacePTR& ui){
			this->id = id;
			
			this->script = script;
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
			script->_delete(); script = nullptr;
			app = nullptr;
		}

		void Layer::Init(RPGApplicationPTR& app){
			this->app = app;
		}

		/* These functions are not required to be implemented in the derived classes */
		void Layer::Load(){
			script->Load();
			canvas->Load();
			ui->Load();
		}
		void Layer::Unload(){
			script->Unload();
			canvas->Unload();
			ui->Unload();
		}
		void Layer::Ready(LayerArgsPTR& args){
			instack = true;

			script->Ready(args);
			canvas->Ready();
			ui->Ready();
		}
		void Layer::Exit(){
			instack = false;

			script->Exit();
			canvas->Exit();
			ui->Exit();
		}

		void Layer::Show(){
			focus = true;
			standby = false;
			hidden = false;

			script->Show();
			canvas->Show();
			ui->Show();
		}
		void Layer::StandBy(){
			focus = false;
			standby = true;
			hidden = false;

			script->StandBy();
			canvas->StandBy();
			ui->StandBy();
		}
		void Layer::Focus(){
			focus = true;
			standby = false;

			script->Focus();
			canvas->Focus();
			ui->Focus();
		}

		void Layer::Update(){
			if( hidden )
				return;
			
			script->Update();
			canvas->Update();
			ui->Update();
		}
		void Layer::Draw(){
			if( hidden )
				return;
			
			canvas->Draw();
			ui->Draw();
		}
		
		void Layer::StandByHide(bool val){
			hidden = val;
		}
	}
}