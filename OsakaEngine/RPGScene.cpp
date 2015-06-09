 #include "stdafx.h"

#include "Layer.h"
#include "SceneScript.h"
#include "RPGScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGScene::RPGScene(std::string id, SceneScriptPTR& mainscript){
			this->id = id;
			this->mainscript = mainscript;

			focus = false;
			standby = false;
			instack = false;
			hidden = false;
			stackHasChanged = true;
			
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
			mainscript->_delete(); mainscript = nullptr;
			temp_stack_layers.clear();
			stack_layers.clear();
			for(auto it = layers.begin(); it != layers.end(); ++it ){
				it->second->_delete(); 
				//it->second = nullptr; Not needed because when destroying the list (clear), it is automatically set free.
			}
			layers.clear();
		}
		std::string RPGScene::GetId(){
			return this->id;
		}
		
		void RPGScene::Load(){}
		void RPGScene::Load(RPGFactoryPTR& factory){
			mainscript->Load(factory);
			for( auto it = layers.begin(); it != layers.end(); ++it){
				it->second->Load(factory);
			}
		}
		void RPGScene::Unload(){
			mainscript->Unload();
			for( auto it = layers.begin(); it != layers.end(); ++it){
				it->second->Unload();
			}
		}
		void RPGScene::ReadyStandBy(Engine::ESceneArgsPTR& params){
			instack = true;
			focus = false;
			standby = true;

			mainscript->Ready(params);
			mainscript->StandBy();
		}
		void RPGScene::ReadyShow(Engine::ESceneArgsPTR& params){
			instack = true;
			focus = true;
			standby = false;

			mainscript->Ready(params);
			mainscript->Show();
		}

		void RPGScene::Exit(){
			instack = false;
			focus = false;
			standby = false;

			mainscript->Exit();
			/* Removes only the layers that are in stack_layer */
			RemoveAll();
		}

		void RPGScene::Focus(){
			focus = true;
			standby = false;
			mainscript->Focus();
		}
		void RPGScene::StandBy(){
			focus = false;
			standby = true;
			mainscript->StandBy();
		}

		void RPGScene::Add(LayerPTR layer){
			if( layers.find(layer->id) != layers.end() ){
				throw std::exception("[RPGScene] Duplicated layer id.");
			}
			/* This function can only be called inside a SceneBuilder */
			layers[layer->id] = layer;
			//You can't add layers inside the loop. stackHasChanged = true;
		}
		void RPGScene::Stack(std::string id, LayerArgsPTR& args){
			if( stack_layers.size() > 0 ){
				stack_layers.front()->StandBy();
			}
			layers[id]->Ready(args);
			layers[id]->Show();
			stack_layers.push_back(layers[id]);
			stackHasChanged = true;
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
			stackHasChanged = true;
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
			stackHasChanged = true;
		}
		void RPGScene::Switch(std::string id, LayerArgsPTR& args){
			//Removes all
			RemoveAll();
			layers[id]->Ready(args);
			layers[id]->Show();
			stack_layers.push_back(layers[id]);
			stackHasChanged = true;
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
			stackHasChanged = true;
		}
		void RPGScene::RemoveAll(){
			for( auto it = stack_layers.begin(); it != stack_layers.end(); ++it){
				(*it)->Exit();
			}
			stack_layers.clear();
			stackHasChanged = true;
		}

		void RPGScene::Update(){
			if( hidden )
				return;
			mainscript->Update();

			if( stackHasChanged ){
				temp_stack_layers = stack_layers;
				stackHasChanged = false;
			}

			for( auto it = temp_stack_layers.begin(); it != temp_stack_layers.end(); ++it){
				(*it)->Update();
			}
		}
		void RPGScene::Draw(){
			if( hidden )
				return;
			
			for( auto it = temp_stack_layers.begin(); it != temp_stack_layers.end(); ++it){
				(*it)->Draw();
			}
		}
		
		void RPGScene::StandByHide(bool val){
			hidden = val;
		}
		
		void RPGScene::Enter(){
			mainscript->Enter();
			for(auto it = layers.begin(); it != layers.end(); ++it ){
				it->second->Enter(); 
			}
		}
		void RPGScene::End(){
			for(auto it = layers.begin(); it != layers.end(); ++it ){
				it->second->End(); 
			}
			mainscript->End();
		}
	}
}