 #include "stdafx.h"

#include "OneLayer.h"
#include "OneLayerScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		OneLayerScene::OneLayerScene(const std::string& id, SceneScript* mainscript, OneLayer* onelayer) : RPGScene(id, mainscript){
			this->onelayer = onelayer;
		}
		OneLayerScene::~OneLayerScene(){
			delete onelayer; onelayer = NULL;
		}
		
		void OneLayerScene::Load(RPGFactory& factory){
			onelayer->Load(factory);
		}
		void OneLayerScene::Unload(){
			onelayer->Unload();
		}
		void OneLayerScene::ReadyStandBy(Engine::ESceneArgs& params){
			instack = true;
			focus = false;
			standby = true;

			onelayer->Ready(params);
			onelayer->StandBy();
		}
		void OneLayerScene::ReadyShow(Engine::ESceneArgs& params){
			instack = true;
			focus = true;
			standby = false;

			onelayer->Ready(params);
			onelayer->Show();
		}

		void OneLayerScene::Exit(){
			instack = false;
			focus = false;
			standby = false;

			onelayer->Exit();
		}

		void OneLayerScene::Focus(){
			focus = true;
			standby = false;
			onelayer->Focus();
		}
		void OneLayerScene::StandBy(){
			focus = false;
			standby = true;
			onelayer->StandBy();
		}

		void OneLayerScene::Update(){
			if( hidden )
				return;
			onelayer->Update();
		}
		void OneLayerScene::Draw(){
			if( hidden )
				return;
			
			onelayer->Draw();
		}
		
	}
}