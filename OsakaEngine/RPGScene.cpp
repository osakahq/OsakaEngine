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
			this->raw_mainscript = mainscript.get();

			focus = false;
			standby = false;
			instack = false;
			hidden = false;
			stackHasChanged = true;
			started = false;
			//It is recommended to `layers.reserve(x)` to the actual max of layers.
			map_size = 0;
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
			raw_mainscript = NULL;
			mainscript->_delete(); mainscript = nullptr;

			raw_layers.clear();
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
			raw_mainscript->Load(factory);
			for(int i = 0; i < map_size; ++i){
				array_raw_layers[i]->Load(factory);
			}
		}
		void RPGScene::Unload(){
			raw_mainscript->Unload();
			for(int i = 0; i < map_size; ++i){
				array_raw_layers[i]->Unload();
			}
		}
		void RPGScene::ReadyStandBy(Engine::ESceneArgsPTR& params){
			instack = true;
			focus = false;
			standby = true;

			raw_mainscript->Ready(params);
			raw_mainscript->StandBy();
		}
		void RPGScene::ReadyShow(Engine::ESceneArgsPTR& params){
			instack = true;
			focus = true;
			standby = false;

			raw_mainscript->Ready(params);
			raw_mainscript->Show();
		}

		void RPGScene::Exit(){
			instack = false;
			focus = false;
			standby = false;

			raw_mainscript->Exit();
			/* Removes only the layers that are in stack_layer */
			RemoveAll();
		}

		void RPGScene::Focus(){
			focus = true;
			standby = false;
			raw_mainscript->Focus();
		}
		void RPGScene::StandBy(){
			focus = false;
			standby = true;
			raw_mainscript->StandBy();
		}
		void RPGScene::Start(){
			started = true;
		}
		void RPGScene::Add(LayerPTR layer){
			if( started ){
				throw std::exception("[RPGScene] Can't add layers when the loop has started.");
			}
			if( layers.find(layer->id) != layers.end() ){
				throw std::exception("[RPGScene] Duplicated layer id.");
			}
			/* This function can only be called inside a SceneBuilder */
			layers[layer->id] = layer;
			raw_layers[layer->id] = layer.get();
			//First grabs value then increments
			array_raw_layers[map_size++] = layer.get();
			//You can't add layers inside the loop. stackHasChanged = true;
		}
		void RPGScene::Stack(std::string id, LayerArgsPTR& args){
			printf("[RPGScene] Stack\n");
			if( stack_layers.size() > 0 ){
				stack_layers.back()->StandBy();
			}
			Layer* layer = raw_layers[id];
			layer->Ready(args);
			layer->Show();
			//When you add to last, it will be drawn last, making it the "first" one on the stack.
			stack_layers.push_back(layer);
			stackHasChanged = true;
		}
		void RPGScene::StackBefore(std::string id, std::string ref_layer, LayerArgsPTR& args){
			printf("[RPGScene] StackBefore\n");
			Layer* layer = raw_layers[id];
			auto it = std::find(stack_layers.begin(), stack_layers.end(), raw_layers[ref_layer]);
			if( it == stack_layers.end() ){
				throw new std::exception("[RPGScene] Layer not found.");
			}
			
			layer->Ready(args);
			layer->StandBy();
			//Insert functions inserts the element BEFORE the element
			stack_layers.insert(it, layer);
			stackHasChanged = true;
		}
		void RPGScene::StackAfter(std::string id, std::string ref_layer, LayerArgsPTR& args){
			printf("[RPGScene] StackAfter\n");
			Layer* layer_stack = raw_layers[id];
			Layer* layer_ref = raw_layers[ref_layer];
			auto it_ref = std::find(stack_layers.begin(), stack_layers.end(), layer_ref);
			if( it_ref == stack_layers.end() ){
				throw new std::exception("[RPGScene] Layer not found.");
			}

			layer_stack->Ready(args);
			if( stack_layers.size() == 1 ){
				stack_layers.push_back(layer_stack);
				layer_ref->StandBy(); //Loses focus.
				layer_stack->Show(); //Gains focus.

			}else if( ++it_ref == stack_layers.end() ){ //Do not be confused with `.end()`. Begin points to the first one while end points to `past-the-end`
				stack_layers.push_back(layer_stack);

				//Means we are replacing the top place.
				layer_ref->StandBy(); //Loses focus.
				layer_stack->Show(); //Gains focus.
			}else{
				//Insert functions inserts the element BEFORE the element, that's why we need to go 1 position+
				stack_layers.insert(it_ref+1, layer_stack);
				layer_stack->StandBy();
			}
			
			stackHasChanged = true;
		}
		void RPGScene::Switch(std::string id, LayerArgsPTR& args){
			printf("[RPGScene] Switch\n");
			//Removes all
			RemoveAll();
			Layer* layer = raw_layers[id];
			layer->Ready(args);
			layer->Show();
			stack_layers.push_back(layer);
			stackHasChanged = true;
		}
		void RPGScene::Remove(std::string id){
			printf("[RPGScene] Remove\n");
			if( stack_layers.size() == 1 ){
				raw_layers[id]->Exit();
				stack_layers.clear();
			}else{
				Layer* layer = raw_layers[id];
				auto it = std::find(stack_layers.begin(), stack_layers.end(), layer);
				if( it == stack_layers.end() ){
					throw new std::exception("[RPGScene] Layer not found.");
				}
				if( ++it == stack_layers.end() ){
					//If position of the elemnt to remove is top(begin) then the soon to be first, needs to have Focus function called.
					stack_layers.erase(it);
					stack_layers.back()->Focus();
				}else{
					stack_layers.erase(it);
				}
				layer->Exit();
			}
			stackHasChanged = true;
		}
		void RPGScene::RemoveAll(){
			printf("[RPGScene] RemoveAll\n");
			int quantity = stack_layers.size();
			std::copy(stack_layers.begin(), stack_layers.end(), copy_stack_layers);
			stack_layers.clear();

			for(int i = 0; i < quantity; ++i){
				copy_stack_layers[i]->Exit();
			}
			stackHasChanged = true;
		}

		void RPGScene::Update(){
			if( hidden )
				return;
			raw_mainscript->Update();

			if( stackHasChanged ){
				printf("[RPGScene] Update -> stackHasChanged\n");
				temp_stack_layers_items = stack_layers.size();
				std::copy(stack_layers.begin(), stack_layers.end(), temp_stack_layers);
				stackHasChanged = false;
			}
			for(int i = 0; i < temp_stack_layers_items; ++i){
				temp_stack_layers[i]->Update();
			}
		}
		void RPGScene::Draw(){
			if( hidden )
				return;
			for(int i = 0; i < temp_stack_layers_items; ++i){
				temp_stack_layers[i]->Draw();
			}
		}
		
		void RPGScene::StandByHide(bool val){
			hidden = val;
		}
		
		void RPGScene::Enter(){
			printf("[RPGScene] Enter\n");
			raw_mainscript->Enter();
			for(int i = 0; i < map_size; ++i){
				array_raw_layers[i]->Enter();
			}
		}
		void RPGScene::End(){
			for(int i = 0; i < map_size; ++i){
				array_raw_layers[i]->End();
			}
			raw_mainscript->End();
		}
	}
}