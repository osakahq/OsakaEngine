 #include "stdafx.h"
#include "EScene.h"
#include "Canvas.h"
#include "UserInterface.h"
#include "Script.h"
#include "RPGApplication.h"
#include "RPGScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGScene::RPGScene(std::string id, RPGApplicationPTR& app, CanvasPTR& canvas, UserInterfacePTR& ui, ScriptPTR& script){
			this->id = id;
			this->app = app;

			this->canvas = canvas;
			this->ui = ui;
			this->script = script;

			focus = false;
			standby = false;
			instack = false;
			hidden = false;
		}
		RPGScene::~RPGScene(){
#ifdef _DEBUG
			_CHECKDELETE("RPGScene");
#endif			
		}
		void RPGScene::_delete(){
#ifdef _DEBUG
			_CHECKDELETE("RPGScene_delete");
#endif
			//The order in which they are deleted matters.
			script->_delete(); script= nullptr;
			canvas->_delete(); canvas = nullptr;
			ui->_delete(); ui = nullptr;
			app = nullptr;
		}
		std::string RPGScene::GetId(){
			return this->id;
		}
		void RPGScene::Init(){
			
		}
		void RPGScene::Load(){
			script->Load();
			ui->Load();
			canvas->Load();
		}
		void RPGScene::Unload(){
			script->Unload();
			ui->Unload();
			canvas->Unload();
		}
		void RPGScene::ReadyStandBy(Engine::ESceneArgsPTR& params){
			instack = true;
			focus = false;
			standby = true;

			script->Ready(params);
			ui->Ready();
			canvas->Ready();

			script->StandBy();
			ui->StandBy();
			canvas->StandBy();
		}
		void RPGScene::ReadyShow(Engine::ESceneArgsPTR& params){
			instack = true;
			focus = true;
			standby = false;

			script->Ready(params);
			ui->Ready();
			canvas->Ready();

			script->Show();
			ui->Show();
			canvas->Show();
		}

		void RPGScene::Exit(){
			instack = false;
			focus = false;
			standby = false;

			script->Exit();
			ui->Exit();
			canvas->Exit();
		}

		void RPGScene::Focus(){
			focus = true;
			standby = false;

			script->Focus();
			ui->Focus();
			canvas->Focus();
		}
		void RPGScene::StandBy(){
			focus = false;
			standby = true;

			script->StandBy();
			ui->StandBy();
			canvas->StandBy();
		}

		void RPGScene::Update(){
			if( hidden )
				return;
			script->Update();
			ui->Update();
			canvas->Update();
		}
		void RPGScene::Draw(){
			if( hidden )
				return;
			script->Draw();
			ui->Draw();
			canvas->Draw();
		}

		void RPGScene::StandByHide(){
			//Toggle
			hidden = (hidden) ? false : true;
		}
	}
}