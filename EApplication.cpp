 #include "stdafx.h"
#include "SDLLib.h"
#include "Debug.h"
#include "EScenePassParams.h"
#include "EScene.h"
#include "IFileLoader.h"
#include "EApplication.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace Engine{
		EApplication::EApplication(Debug::DebugPTR& d, SDLLibPTR& sdl, IFileLoaderPTR& fileloader){
			this->sdl = sdl;
			this->debug = d;
			
			stackItems = -1;
			stackHasChanged = true;
			this->fileloader = fileloader;

		}
		EApplication::~EApplication(){
#ifdef _DEBUG
			_CHECKDELETE("EApplication");
#endif			
		}
		void EApplication::_delete(){
			for(auto it = scenes.begin(); it != scenes.end(); ++it )
				it->second->_delete();
			scenes.clear();
			sdl->_delete(); sdl = nullptr;
			fileloader->_delete(); fileloader = nullptr;
			debug = nullptr;
		}
		void EApplication::Init(){
			
		}
		void EApplication::AddScene(std::string id, EScenePTR& scene){
			//Takes ownership of the scene
			scenes[id] = scene;
		}

		void EApplication::Switch(const char* scene, EScenePassParamsPTR& in_param){
			RemoveAllFromStack();
			stackItems++;
			stack[stackItems] = scene;
			scenes[scene]->Show(in_param);
			stackHasChanged = true;
		}
		void EApplication::Stack(const char* scene, EScenePassParamsPTR& in_param){
			//We only need to call StandBy on current top scene because the others are already in standby
			this->scenes[stack[this->stackItems]]->StandBy();

			stackItems++;
			stack[stackItems] = scene;
			scenes[scene]->Show(in_param);
			stackHasChanged = true;
		}
		void EApplication::BottomStack(const char* scene, EScenePassParamsPTR& in_param){
			//We push the array 1 position so we leave 0 free
			for(int i = this->stackItems; i >= 0; i--){
				stack[i+1] = stack[i];
			}
			
			stackItems++;
			stack[0] = scene;
			scenes[scene]->StandBy(in_param);	
			stackHasChanged = true;
		}
		void EApplication::Remove(const char* scene){
			int position = -1;
			for(int i = 0; i <= this->stackItems; i++){
				if( strcmp(stack[i].c_str(), scene) == 0 ){
					position = i;
					break;
				}
			}
			if( position == -1 ){
				debug->e("[EApplication] Unkown scene (Remove function).");
			}

			if( position == stackItems ){
				//If the scene to remove is top, then we have to let the next one scene know it is its turn
				scenes[stack[stackItems]]->Focus();
			}

			scenes[stack[position]]->Hide();
			//We move the array backwards, effectively replacing the scene to remove
			for(int i = position; i <= this->stackItems; i++){
				stack[i] = stack[i+1];
			}
			stackItems--;
			stackHasChanged = true;
		}
		void EApplication::RemoveAllFromStack(const char* except_scene){
			bool gainedFocus = false;

			for(int i = 0; i <= this->stackItems; i++){
				if( except_scene != NULL && strcmp(stack[i].c_str(), except_scene) == 0 ){
					if( i != this->stackItems ){
						/* This means the scene wasn't at top and Focus() needs to be called */
						gainedFocus = true;
					}
					//We just don't call Hide();
					continue;

				}
				this->scenes[stack[i]]->Hide();
			}
			this->stackItems = -1;
			stackHasChanged = true;

			if( except_scene != NULL ){
				stackItems++;
				stack[stackItems] = except_scene;
				/* If the except_scene wasn't at the top, then it Focus() needs to be called */
				if( gainedFocus )
					scenes[stack[stackItems]]->Focus();
			}
		}

		void EApplication::Run(){
			/* See SDLLib:ShowWindow().h for explanation */
			sdl->ShowWindow();
			debug->l("[TODO EApp] SDL DELAY");
			
			bool quit = false;
			SDL_Event e;

			std::string tempStack[EAPP_MAXSTACK];
			int tempStackItems = 0;
			
			while(!quit){
				while( SDL_PollEvent(&e) != 0 ){
					if( e.type == SDL_QUIT ){
						quit = true;
					}
				}
				/* We need to copy it because a scene in `Update()` can mess the stack/loop 
				 * The changes are not "seen" until the next update. */
				if( stackHasChanged ){
					stackHasChanged = false;
					tempStackItems = this->stackItems;
					for(int i = 0; i <= this->stackItems; i++){
						tempStack[i] = stack[i];
					}
				}

				this->Update();
				for(int i = 0; i <= tempStackItems; i++){
					this->scenes[tempStack[i]]->Update();
				}
				sdl->Clear();
				for(int i = 0; i <= tempStackItems; i++){
					this->scenes[tempStack[i]]->Draw();
				}
				sdl->Render();
				//Remove this
				SDL_Delay(17);
			}
			

		}
		void EApplication::Update(){/* Nothing for now */}
	}
}