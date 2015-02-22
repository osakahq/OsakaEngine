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
			this->canvas = canvas;
			this->ui = ui;
			this->script = script;
			this->app = app;
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
		void RPGScene::Show(Engine::EScenePassParamsPTR& params){
			script->Show(params);
			ui->Show();
			canvas->Show();
		}
		void RPGScene::Hide(){
			script->Hide();
			ui->Hide();
			canvas->Hide();
		}
		void RPGScene::StandBy(){
			script->StandBy();
			ui->StandBy();
			canvas->StandBy();
		}
		void RPGScene::StandBy(Engine::EScenePassParamsPTR& params){
			script->StandBy(params);
			ui->StandBy();
			canvas->StandBy();
		}
		void RPGScene::Focus(){
			script->Focus();
			ui->Focus();
			canvas->Focus();
		}
		void RPGScene::Update(){
			script->Update();
			ui->Update();
			canvas->Update();
		}
		void RPGScene::Draw(){
			script->Draw();
			ui->Draw();
			canvas->Draw();
		}
		void RPGScene::Reset(){
			script->Reset();
			ui->Reset();
			canvas->Reset();
		}

		void RPGScene::StandByHide(){

		}
	}
}