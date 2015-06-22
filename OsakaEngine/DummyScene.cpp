 #include "stdafx.h"
#include "DummyScene.h"
namespace Osaka{
	namespace RPGLib{
		DummyScene::DummyScene(const std::string& id, SceneScript* mainscript) : RPGScene(id, mainscript){
			
		}
		DummyScene::~DummyScene(){
		
		}
		
		void DummyScene::ReadyShow(Engine::ESceneArgs& params){
			
		}
		
		void DummyScene::Update(Engine::keyboard_state& state){
			
		}
		
		void DummyScene::Start(){};
		void DummyScene::Enter(){};
		void DummyScene::Load(RPGFactory& factory){}
		void DummyScene::Load(){};
		void DummyScene::Unload() {};
		void DummyScene::Exit() {};
		void DummyScene::ReadyStandBy(Engine::ESceneArgs& params) {};
		void DummyScene::StandBy() {};
		void DummyScene::Focus() {};
		void DummyScene::Draw() {};
		void DummyScene::End() {};
	}
}