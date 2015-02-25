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
		void EApplication::Init(bool vsync, int timePerFrame){
			this->vsync = vsync;
			this->timePerFrame = timePerFrame;
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
			
			if( position == stackItems && stackItems > 0 ){
				//If the scene to remove is top and there is more than 1, then we have to let the next one(-1 from position) scene know it is its turn
				scenes[stack[position-1]]->Focus();
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
			
			const bool _vsync = vsync;
			const Uint32 _targetTimePerFrame = timePerFrame;
			Uint32 frame_ms = 0;

			while(!quit){
				frame_ms = SDL_GetTicks();
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
				this->BeforePresent();
				sdl->Present();

#ifdef _DEBUG
				this->RenderTime(SDL_GetTicks() - frame_ms);
#endif
				//_vsync is a constant = no branch problem
				if( !_vsync ){
					if( _targetTimePerFrame > (SDL_GetTicks() - frame_ms) ){
						//if 16 > 10 then-> 16 - 10 = 6ms to delay
						SDL_Delay(_targetTimePerFrame - (SDL_GetTicks() - frame_ms));
					}
				}

				//Para revisar el FPS cuando NO es debug, es en FPSCounter
#ifdef _DEBUG
				//Esto va despues para tomar en cuenta el delay, y estar seguros que aun con el delay, no pasen de 16ms
				if( _vsync ){
					if( (SDL_GetTicks() - frame_ms) > _targetTimePerFrame+1 ){
						//Se pone FPS_TARGET_MS_PER_FRAME+1 porque en VSYNC siempre es 17/16ms por frame.
						printf("[FPS] Last frame took longer than expected to render.\n");
					}
				}else{
					if( (SDL_GetTicks() - frame_ms) > _targetTimePerFrame ){
						printf("[FPS] Last frame took longer than expected to render.\n");
					}
				}
#endif
			}
		}
		void EApplication::Update(){/* Nothing for now */}
		void EApplication::BeforePresent(){/* Nothing for now */}
		//void EApplication::RenderTime(Uint32 frame_ms){}
	}
}