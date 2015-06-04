 #include "stdafx.h"
#include "SDLLib.h"
#include "Debug.h"
#include "ESceneArgs.h"
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
			for(int i = 0; i < EAPP_MAXSTACK; ++i){
				stack[i] = nullptr;
			}
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
		void EApplication::CallLoad(std::string id){
			scenes[id]->Load();
		}

		void EApplication::Switch(const char* scene, ESceneArgsPTR& in_param){
			RemoveAllFromStack();
			stackItems++;
			stack[stackItems] = scenes[scene];
			scenes[scene]->ReadyShow(in_param);
			stackHasChanged = true;
		}
		void EApplication::Stack(const char* scene, ESceneArgsPTR& in_param){
			//We only need to call StandBy on current top scene because the others are already in standby
			stack[this->stackItems]->StandBy();

			stackItems++;
			stack[stackItems] = scenes[scene];
			scenes[scene]->ReadyShow(in_param);
			stackHasChanged = true;
		}
		void EApplication::BottomStack(const char* scene, ESceneArgsPTR& in_param){
			//We push the array 1 position so we leave 0 free
			for(int i = this->stackItems; i >= 0; i--){
				stack[i+1] = stack[i];
			}
			
			stackItems++;
			stack[0] = scenes[scene];
			scenes[scene]->ReadyStandBy(in_param);	
			stackHasChanged = true;
		}
		void EApplication::Remove(const char* scene){
			int position = -1;
			for(int i = 0; i <= this->stackItems; i++){
				if( strcmp(stack[i]->GetId().c_str(), scene) == 0 ){
					position = i;
					break;
				}
			}
			if( position == -1 ){
				debug->e("[EApplication] Unkown scene (Remove function).");
			}
			
			if( position == stackItems && stackItems > 0 ){
				//If the scene to remove is top and there is more than 1, then we have to let the next one(-1 from position) scene know it is its turn
				stack[position-1]->Focus();
			}

			stack[position]->Exit();
			//We move the array backwards, effectively replacing the scene to remove
			for(int i = position; i <= this->stackItems; i++){
				stack[i] = stack[i+1];
			}
			stackItems--;
			stackHasChanged = true;
		}
		void EApplication::RemoveAllFromStack(const char* except_scene){
			//default parameter except_scene = NULL
			bool gainedFocus = false;

			for(int i = 0; i <= this->stackItems; i++){
				if( except_scene != NULL && strcmp(stack[i]->GetId().c_str(), except_scene) == 0 ){
					if( i != this->stackItems ){
						/* This means the scene (except scene) wasn't at top and Focus() needs to be called */
						gainedFocus = true;
					}
					//We just don't call Hide();
					continue;

				}
				stack[i]->Exit();
			}
			this->stackItems = -1;
			stackHasChanged = true;

			if( except_scene != NULL ){
				stackItems++;
				stack[stackItems] = scenes[except_scene];
				/* If the except_scene wasn't at the top, then it Focus() needs to be called */
				if( gainedFocus )
					stack[stackItems]->Focus();
			}
		}

		void EApplication::Run(){
			/* See SDLLib:ShowWindow().h for explanation */
			sdl->ShowWindow();
			
			bool quit = false;
			SDL_Event e;

			EScenePTR tempStack[EAPP_MAXSTACK];
			int tempStackItems = 0;
			
			const bool _vsync = vsync;
			const Uint32 _targetTimePerFrame = timePerFrame;
			Uint32 frame_ms = 0;
			Uint32 total_frame_ms = 0; //This is used when vsync is off

			debug->l("[EApplication] Loop begins...\n\n");
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
#ifdef _DEBUG
					debug->l("[EApplication] Current scenes in stack: (order from bottom to top)");
#endif
					for(int i = 0; i <= this->stackItems; i++){
						tempStack[i] = stack[i];
#ifdef _DEBUG
						debug->l("[EApplication] \t\t"+std::to_string(i)+": "+stack[i]->GetId());
#endif
					}
				}

				this->Update();
				for(int i = 0; i <= tempStackItems; i++){
					tempStack[i]->Update();
				}
				sdl->Clear();
				for(int i = 0; i <= tempStackItems; i++){
					tempStack[i]->Draw();
				}
				this->BeforePresent();
				sdl->Present();
				
				//You need to substract with SDL_GetTicks() in order to know how much the frame took.
				this->AfterPresent(frame_ms);
				
				//_vsync is a constant = no branch problem
				if( !_vsync ){
					total_frame_ms = SDL_GetTicks() - frame_ms;
					//if 16 > 10 then-> 16 - 10 = 6ms to delay
					if( _targetTimePerFrame > total_frame_ms ){
						//I modified it because I don't there there is gonna be much difference
						//Also, SDL_Delay may return 1ms earlier
						//SDL_Delay(_targetTimePerFrame - (SDL_GetTicks() - frame_ms));
						SDL_Delay(_targetTimePerFrame - total_frame_ms);
					}
				}

				//Para revisar el FPS cuando NO es debug, es en FPSCounter
#ifdef _DEBUG
				//Esto va despues para tomar en cuenta el delay, y estar seguros que aun con el delay, no pasen de 16ms
				if( _vsync ){
					if( (SDL_GetTicks() - frame_ms) > _targetTimePerFrame+2 ){
						//Se pone FPS_TARGET_MS_PER_FRAME+1 porque en VSYNC siempre es 17/16ms por frame. A veces hasta 18ms, pero es muy exacto para tener 60fps
						printf("[FPS] Last frame took longer than expected to render.\n");
					}
				}else{
					//This also has +1 because it is never perfect and sometimes it does 17ms delay
					if( (SDL_GetTicks() - frame_ms) > _targetTimePerFrame+1 ){
						printf("[FPS] Last frame took longer than expected to render.\n");
					}
				}
#endif
			}
		}
		//void EApplication::Update(){/* Nothing for now */}
		//void EApplication::BeforePresent(){/* Nothing for now */}
		//void EApplication::RenderTime(const Uint32 frame_ms){}
	}
}