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
			enteringItems = -1;
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
			for(int i = 0; i < EAPP_MAXSTACK; ++i){
				entering[i] = nullptr;
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
			entering[++enteringItems] = stack[stackItems] = scenes[scene];
			scenes[scene]->ReadyShow(in_param); 
			stackHasChanged = true;
		}
		void EApplication::Stack(const char* scene, ESceneArgsPTR& in_param){
			//We only need to call StandBy on current top scene because the others are already in standby
			stack[this->stackItems]->StandBy();

			stackItems++;
			entering[++enteringItems] = stack[stackItems] = scenes[scene];
			scenes[scene]->ReadyShow(in_param);
			stackHasChanged = true;
		}
		void EApplication::BottomStack(const char* scene, ESceneArgsPTR& in_param){
			//We push the array 1 position so we leave 0 free
			for(int i = this->stackItems; i >= 0; i--){
				stack[i+1] = stack[i];
			}
			
			stackItems++;
			entering[++enteringItems] = stack[0] = scenes[scene];
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
			int tempStackItems = -1;
			
			EScenePTR tempEntering[EAPP_MAXSTACK];
			int tempEnteringItems = -1;

			const bool _vsync = vsync;
			const Uint32 _targetTimePerFrame = timePerFrame;
			/* This is only used for debug purposed (Show hiccups, vsync on delay, etc.) 
			 * This is NOT used for game logic. For game logic go to TimeManager.h */
			Uint32 frame_ms = 0;
			Uint32 total_frame_ms = 0; //This is used when vsync is off

#ifdef _DEBUG
			bool pauseFrame = false;
			int framesPerKey = 1;
			int _currentFrame = 0;
			Uint32 paused_time = 0;
#endif

			debug->l("[EApplication] Loop begins...\n\n");
			while(!quit){
				frame_ms = SDL_GetTicks(); //only used for debugging
				while( SDL_PollEvent(&e) != 0 ){
					if( e.type == SDL_QUIT ){
						quit = true;
					}else if( e.type == SDL_KEYDOWN ){
						switch(e.key.keysym.sym){
#ifdef _DEBUG
						case SDLK_F1:
							pauseFrame = (pauseFrame)?false:true;
							framesPerKey = 3;
							_currentFrame = 0;
							break;
#endif
						}
					}
				}

#ifdef _DEBUG
				paused_time = 0;
				if( pauseFrame ){
					//First grabs value then increments, so... we actually wait the for the actual frame to complete.
					if( _currentFrame++ >= framesPerKey ){
						_currentFrame = 0;
						printf("-- Frame is paused, please press enter to continue...");
						paused_time = SDL_GetTicks();
						getchar();
						paused_time = SDL_GetTicks() - paused_time;
					}
				}
#endif
				/* We need to copy it because a scene in `Update()` can mess the stack/loop 
				 * The changes are not "seen" until the next update. */
				if( stackHasChanged ){
					stackHasChanged = false;
					tempStackItems = this->stackItems;
					std::copy(&stack[0], &stack[tempStackItems+1], tempStack);
				}

#ifdef _DEBUG
				//Remeber to call update before these functions (Enter, Update, Draw) (updates TimeManager)
				this->Update(paused_time);
#else
				this->Update();
#endif
				/* The reason this is after tempStack is because if Enter stacks a scene, it will "queue" the enter function but call Update first.
				 * In this order, first copies the tempStack then Enter and Update function will be called in the correct order. */
				if( enteringItems >= 0 ){
					tempEnteringItems = enteringItems;
					enteringItems = -1; //There is no need to set `nullptr`
					//Basically, Enter() is like an early Update. I have decided it's okay to stack inside Enter as well (only Update and Enter)
					std::copy(&entering[0], &entering[tempEnteringItems+1], tempEntering);
					for(int i = 0; i <= tempEnteringItems; ++i){
						tempEntering[i]->Enter();
					}
				}
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
			} //while(!quit)
			//Means we are closing the application...
			for(auto it = scenes.begin(); it != scenes.end(); ++it ){
				it->second->End();
			}
		}
		//void EApplication::Update(){/* Nothing for now */}
		//void EApplication::BeforePresent(){/* Nothing for now */}
		//void EApplication::RenderTime(const Uint32 frame_ms){}
	}
}