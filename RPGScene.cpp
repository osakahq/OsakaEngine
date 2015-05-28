 #include "stdafx.h"
#include "EScene.h"
#include "Layer.h"
#include "RPGApplication.h"
#include "RPGScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGScene::RPGScene(std::string id, RPGApplicationPTR& app){
			this->id = id;
			this->app = app;

			focus = false;
			standby = false;
			instack = false;
			hidden = false;
			//It is recommended to `layers.reserve(x)` to the actual max of layers.
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
			for(auto it = layers.begin(); it != layers.end(); ++it ){
				it->second->_delete(); 
				//it->second = nullptr; Not needed because when destroying the list (clear), it is automatically set free.
			}
			layers.clear();
			app = nullptr;
		}
		std::string RPGScene::GetId(){
			return this->id;
		}
		
		void RPGScene::Load(){
			for( auto it = layers.begin(); it != layers.end(); ++it){
				it->second->Load();
			}
		}
		void RPGScene::Unload(){
			for( auto it = layers.begin(); it != layers.end(); ++it){
				it->second->Unload();
			}
		}
		void RPGScene::ReadyStandBy(Engine::ESceneArgsPTR& params){
			instack = true;
			focus = false;
			standby = true;

			this->ReadyEx(params);
		}
		void RPGScene::ReadyShow(Engine::ESceneArgsPTR& params){
			instack = true;
			focus = true;
			standby = false;

			this->ReadyEx(params);
		}

		void RPGScene::Exit(){
			instack = false;
			focus = false;
			standby = false;

			RemoveAll();
		}

		void RPGScene::Focus(){
			focus = true;
			standby = false;
		}
		void RPGScene::StandBy(){
			focus = false;
			standby = true;
		}

		void RPGScene::Add(LayerPTR layer){
			layers[layer->id] = layer;
		}
		void RPGScene::Stack(std::string id, LayerArgsPTR& args){
			if( stack_layers.size() > 0 ){
				stack_layers.front()->StandBy();
			}
			layers[id]->Ready(args);
			layers[id]->Show();
			stack_layers.push_back(layers[id]);
		}
		void RPGScene::StackBefore(std::string id, std::string ref_layer, LayerArgsPTR& args){
			std::vector<LayerPTR>::const_iterator it_ref;
			for( auto it = stack_layers.begin(); it != stack_layers.end(); ++it){
				if( (*it)->id == ref_layer ){
					it_ref = it;
				}
			}
			if( it_ref == stack_layers.end() ){
				//If it_ref doesn't point to any layer (didn't find the layer)
				throw new std::exception("[RPGScene] Layer not found.");
			}
			layers[id]->Ready(args);
			layers[id]->StandBy();
			stack_layers.insert(it_ref, layers[id]);
		}
		void RPGScene::StackAfter(std::string id, std::string ref_layer, LayerArgsPTR& args){
			std::vector<LayerPTR>::const_iterator it_ref;
			for( auto it = stack_layers.begin(); it != stack_layers.end(); ++it){
				if( (*it)->id == ref_layer ){
					it_ref = it;
				}
			}
			if( it_ref == stack_layers.end() ){
				//If it_ref doesn't point to any layer (didn't find the layer)
				throw new std::exception("[RPGScene] Layer not found.");
			}

			layers[id]->Ready(args);
			if( it_ref == stack_layers.begin() ){ //Do not be confused with `.end()`. Begin points to the first one while end points to `past-the-end`
				//Means we are replacing the top place.
				(*it_ref)->StandBy(); //Loses focus.
				layers[id]->Show(); //Gains focus.
			}else{
				layers[id]->StandBy();
			}
			//Insert functions inserts the element BEFORE the element
			stack_layers.insert(it_ref+1, layers[id]);
		}
		void RPGScene::Switch(std::string id, LayerArgsPTR& args){
			//Removes all
			RemoveAll();
			layers[id]->Ready(args);
			layers[id]->Show();
			stack_layers.push_back(layers[id]);
		}
		void RPGScene::Remove(std::string id){
			if( stack_layers.size() == 1 ){
				layers[id]->Exit();
				stack_layers.clear();
			}else{
				std::vector<LayerPTR>::const_iterator it_rem;
				for( auto it = stack_layers.begin(); it != stack_layers.end(); ++it){
					if( (*it)->id == id ){
						it_rem = it;
					}
				}
				layers[id]->Exit();
				if( it_rem == stack_layers.begin() ){
					//If position of the elemnt to remove is top(begin) then the soon to be first, needs to have Focus function called.
					stack_layers.erase(it_rem);
					stack_layers.front()->Focus();
				}else{
					stack_layers.erase(it_rem);
				}
			}
			
		}
		void RPGScene::RemoveAll(){
			for( auto it = stack_layers.begin(); it != stack_layers.end(); ++it){
				(*it)->Exit();
			}
			stack_layers.clear();
		}

		void RPGScene::Update(){
			if( hidden )
				return;
			//I had to add this so I don't have to worry about adding `if( hidden )` to the derived class.
			this->UpdateEx();
			for( auto it = stack_layers.begin(); it != stack_layers.end(); ++it){
				(*it)->Update();
			}
		}
		void RPGScene::Draw(){
			if( hidden )
				return;
			for( auto it = stack_layers.begin(); it != stack_layers.end(); ++it){
				(*it)->Draw();
			}
		}
		
		void RPGScene::StandByHide(){
			//Toggle
			hidden = (hidden) ? false : true;
		}
		void RPGScene::UpdateEx(){
			//Dummy
		}
		void RPGScene::ReadyEx(Engine::ESceneArgsPTR& params){
			//Dummy
		}

	}
}