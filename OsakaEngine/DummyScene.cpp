 #include "stdafx.h"
#include "DummyScene.h"
namespace Osaka{
	namespace RPGLib{
		DummyScene::DummyScene(std::string id, SceneScriptPTR& mainscript) : RPGScene(id, mainscript){
			
		}
		DummyScene::~DummyScene(){
		
		}
		void DummyScene::_delete(){
			RPGScene::_delete();
		}
		std::string DummyScene::GetId(){
			return id;
		}
		
		void DummyScene::ReadyShow(Engine::ESceneArgsPTR& params){
			
		}
		
		void DummyScene::Update(){
			
		}
		
		void DummyScene::Enter(){};
		void DummyScene::Load(RPGFactoryPTR& factory){}
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