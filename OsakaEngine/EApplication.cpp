 #include "stdafx.h"
#include "SDLLib.h"
#include "Debug.h"
#include "ConsoleColors.h"
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
			Uint32 total_frame_ms = 0; //This is used when vsync is off
			const Uint32 _targetTimePerFrame = timePerFrame; //16 for 60fps
			
			/* start is also used to cap the framerate when vsync is off */
			Uint32 start = 0;
			Uint32 old_start = 0;
			
			//160ms which equals to roughly 10 updates max.
			const Uint32 max_delta = 160;
			//Delta is the elapsed time since the last => (SDL_GetTicks())
			Uint32 delta = 0;
			Uint32 accumulated_delta = 0;
			
#ifdef _DEBUG
			bool pause_frame = false;
			const int frames_per_key = 3;
			int current_frame = 0;
			Uint32 total_paused_time = 0;
#endif

			debug->l("[EApplication] Loop begins...\n\n");
			old_start = SDL_GetTicks();
			while(!quit){
#ifdef _DEBUG
				//We need to make sure "start" is not modified so that there isn't a delay in vsync if we are behind.
				start = SDL_GetTicks() - total_paused_time;
				if( pause_frame ){
					//First grabs value then increments, so... we actually wait the for the actual frame to complete.
					if( current_frame++ >= frames_per_key ){
						current_frame = 0;
						printf("-- Frame is paused, please press enter to continue...");
						Uint32 paused_time = SDL_GetTicks();
						getchar();
						total_paused_time += SDL_GetTicks() - paused_time;
						start -= paused_time;
					}
				}
#else
				start = SDL_GetTicks();
#endif
				delta = start - old_start;
				//Cap delta time and make the overflowed elapsed time go away
				if( delta > max_delta ){
					/* I'm not sure how to explain why we don't need to modify start 
					 *  . The next delta will the correct time (how long it took to go through the whole loop) */
					delta = max_delta;
				}
				old_start = start;

				accumulated_delta += delta;
				/* If delta is lower than 16ms, that's fine. But it won't process `accumulated_delta` lower than 16ms */
				if( delta > _targetTimePerFrame ){
					std::cout << Debug::yellow;
					printf("[EApplication] Delta is higher than target ms = %d\n", delta);
					std::cout << Debug::white;
					delta = _targetTimePerFrame;
				}
				
				bool first_loop = true;
				do{ //while(accumulated_delta >= _targetTimePerFrame);
					if( first_loop ){
						//We have to do this because sometimes SDL_Delay returns 1ms earler, making delta 15ms sometimes.
						accumulated_delta -= delta;
						first_loop = false;
					}else{
						//We are setting delta a value of 16ms then substracting that to accumulated_delta
						accumulated_delta -= delta = _targetTimePerFrame;
						printf("[EApplication] Catching up...\n");
					}

					while( SDL_PollEvent(&e) != 0 ){
						if( e.type == SDL_QUIT ){
							quit = true;
						}else if( e.type == SDL_KEYDOWN ){
#ifdef _DEBUG
							switch(e.key.keysym.sym){
							case SDLK_F1:
								pause_frame = (pause_frame) ? false : true;
								current_frame = 0;
								break;
							}
#endif
						}
					}

					/* We need to copy it because a scene in `Update()` can mess the stack/loop 
					 * The changes are not "seen" until the next update. */
					if( stackHasChanged ){
						stackHasChanged = false;
						tempStackItems = this->stackItems;
						std::copy(&stack[0], &stack[tempStackItems+1], tempStack);
					}
					/* This has to be before any scene function because it updates TimeManager */
					this->Update(delta);
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

				}while(accumulated_delta >= _targetTimePerFrame);

				sdl->Clear();
				for(int i = 0; i <= tempStackItems; i++){
					tempStack[i]->Draw();
				}
				this->BeforePresent();
				sdl->Present();
				
				//You need to substract with SDL_GetTicks() in order to know how much the frame took.
				this->AfterPresent(start);
				
				//This has to be at the end so it's easier to considerate the delay as part of the frame.
				if( !_vsync ){
					total_frame_ms = SDL_GetTicks() - start;
					//if 16 > 10 then-> 16 - 10 = 6ms to delay
					if( _targetTimePerFrame > total_frame_ms ){
						/* SDL_Delay may return 1ms earlier
						 * Old: SDL_Delay(_targetTimePerFrame - (SDL_GetTicks() - frame_ms)); */
						SDL_Delay(_targetTimePerFrame - total_frame_ms);
					}
				}
			} //while(!quit)
			//Means we are closing the application...
			for(auto it = scenes.begin(); it != scenes.end(); ++it ){
				it->second->End();
			}
		}

	}
}