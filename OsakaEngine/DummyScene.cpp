 #include "stdafx.h"
#include "DummyScene.h"
namespace Osaka{
	namespace RPGLib{
		DummyScene::DummyScene(std::string id){
			this->id = id;
		}
		DummyScene::~DummyScene(){
		
		}
		void DummyScene::_delete(){

		}
		std::string DummyScene::GetId(){
			return id;
		}
		
		void DummyScene::ReadyShow(Engine::ESceneArgsPTR& params){
			
		}
		
		void DummyScene::Update(){
			
		}
		
		void DummyScene::Enter(){};
		void DummyScene::Load(){};
		void DummyScene::Unload() {};
		void DummyScene::Exit() {};
		void DummyScene::ReadyStandBy(Engine::ESceneArgsPTR& params) {};
		void DummyScene::StandBy() {};
		void DummyScene::Focus() {};
		void DummyScene::Draw() {};
		void DummyScene::End() {};
	}
}