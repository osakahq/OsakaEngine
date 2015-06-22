 #include "stdafx.h"

#include "RPGApplication.h"
#include "Script.h"
#include "Canvas.h"
#include "UserInterface.h"
#include "Layer.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		Layer::Layer(const std::string& _id, Script* script, Canvas* canvas, UserInterface* ui) 
			: id(_id)
		{
			raw_script = script;
			raw_canvas = canvas;
			raw_ui = ui;

			focus = false;
			instack = false;
			standby = false;
			hidden = false;
		}
		Layer::~Layer(){	
			/* You must *NOT* use external pointers. */
			delete raw_ui;		raw_ui = NULL;
			delete raw_canvas;	raw_canvas = NULL;
			delete raw_script;	raw_script = NULL;

			raw_app = NULL;
		}
		
		void Layer::Init(RPGApplication* app){
			this->raw_app = app;
		}

		/* These functions are not required to be implemented in the derived classes */
		void Layer::Load(RPGFactory& factory){
			raw_script->Load(factory);
			raw_canvas->Load(factory);
			raw_ui->Load(factory);
		}
		void Layer::Unload(){
			raw_script->Unload();
			raw_canvas->Unload();
			raw_ui->Unload();
		}
		void Layer::Ready(LayerArgs& args){
			//args is deleted by the callee.
			instack = true;

			raw_script->Ready(args);
			raw_canvas->Ready();
			raw_ui->Ready();
		}
		void Layer::Exit(){
			instack = false;

			raw_script->Exit();
			raw_canvas->Exit();
			raw_ui->Exit();
		}

		void Layer::Show(){
			focus = true;
			standby = false;
			hidden = false;

			raw_script->Show();
			raw_canvas->Show();
			raw_ui->Show();
		}
		void Layer::StandBy(){
			focus = false;
			standby = true;
			hidden = false;

			raw_script->StandBy();
			raw_canvas->StandBy();
			raw_ui->StandBy();
		}
		void Layer::Focus(){
			focus = true;
			standby = false;

			raw_script->Focus();
			raw_canvas->Focus();
			raw_ui->Focus();
		}

		void Layer::Update(Engine::keyboard_state& state){
			if( hidden )
				return;
			
			raw_script->Update(state);
			raw_canvas->Update(state);
			raw_ui->Update(state);
		}
		void Layer::Draw(){
			if( hidden )
				return;
			
			raw_canvas->Draw();
			raw_ui->Draw();
		}
		
		void Layer::StandByHide(bool val){
			hidden = val;
		}

		void Layer::Enter(){
			raw_script->Enter();
			raw_canvas->Enter();
			raw_ui->Enter();
		}
		void Layer::End(){
			raw_script->End();
			raw_canvas->End();
			raw_ui->End();
		}
	}
}