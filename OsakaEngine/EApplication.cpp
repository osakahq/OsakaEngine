 #include "stdafx.h"
#include "SDLLib.h"
#include "Debug.h"
#include "ConsoleColors.h"
#include "ESceneArgs.h"
#include "EScene.h"
#include "IFileLoader.h"
#include "EApplication.h"
#include "osaka_forward.h"

#ifdef _DEBUG
#define EAPPLICATION_PAUSEFRAME
#endif

namespace Osaka{
	namespace Engine{
		EApplication::EApplication(Debug::DebugPTR& d, SDLLibPTR& sdl, IFileLoaderPTR& fileloader){
			this->sdl = sdl;
			this->debug = d;
			
			stack.reserve(EAPP_MAXSTACK);
			entering.reserve(EAPP_MAXSTACK);
			stackHasChanged = true;
			this->fileloader = fileloader;

		}
		EApplication::~EApplication(){
#ifdef _DEBUG
			_CHECKDELETE("EApplication");
#endif			
		}
		void EApplication::_delete(){
			stack.clear();
			entering.clear();
			
			for(auto it = scenes.begin(); it != scenes.end(); ++it )
				it->second->_delete();
			scenes.clear();
			sdl->_delete(); sdl = nullptr;
			fileloader->_delete(); fileloader = nullptr;
			debug = nullptr;
		}
		void EApplication::Init(bool vsync, int timePerFrame, int maxUpdatesToCatchUp){
			this->vsync = vsync;
			this->timePerFrame = timePerFrame;
			this->maxUpdatesToCatchUp = maxUpdatesToCatchUp;
		}
		void EApplication::AddScene(std::string id, EScenePTR& scene){
			//Takes ownership of the scene
			scenes[id] = scene;
		}
		void EApplication::CallLoad(std::string id){
			scenes[id]->Load();
		}

		void EApplication::Switch(std::string scene, ESceneArgsPTR& in_param){
			RemoveAllFromStack();
			printf("[EApplication] Switch\n");
			EScenePTR sceneptr = scenes[scene];
			stack.push_back(sceneptr);
			entering.push_back(sceneptr);
			sceneptr->ReadyShow(in_param);
			stackHasChanged = true;
		}
		void EApplication::Stack(std::string scene, ESceneArgsPTR& in_param){
			printf("[EApplication] Stack\n");
			if( stack.size() > 0 ){
				//We only need to call StandBy on current top scene because the others are already in standby
				stack[0]->StandBy();
			}
			EScenePTR sceneptr = scenes[scene];

			stack.insert(stack.begin(), sceneptr);
			entering.push_back(sceneptr);

			sceneptr->ReadyShow(in_param);
			stackHasChanged = true;
		}
		void EApplication::BottomStack(std::string scene, ESceneArgsPTR& in_param){
			printf("[EApplication] BottomStack\n");
			EScenePTR sceneptr = scenes[scene];

			stack.push_back(sceneptr);
			entering.push_back(sceneptr);

			sceneptr->ReadyStandBy(in_param);
			stackHasChanged = true;
		}
		void EApplication::Remove(std::string scene){
			printf("[EApplication] Remove\n");
			auto it = std::find(stack.begin(), stack.end(), scenes[scene]);
			if( it == stack.end() ){
				debug->e("[EApplication] Unkown scene (Remove function).");
			}
			if( it == stack.begin() && stack.size() > 0 ){
				//If the scene to remove is top and there is more than 1, then we have to let the next one(-1 from position) scene know it is its turn
				(*(it+1))->Focus();
			}
			(*it)->Exit();
			stack.erase(it);
			stackHasChanged = true;
		}
		void EApplication::RemoveAllFromStack(std::string except_scene){
			printf("[EApplication] RemoveAllFromStack\n");
			//default parameter except_scene = ""
			if( except_scene.empty() == false ){
				auto it = std::find(stack.begin(), stack.end(), scenes[except_scene]);
				if( it == stack.end() ){
					debug->e("[EApplication] except_scene was not found.");
				}
				//int pos = it - stack.begin();
				if( it != stack.begin() ){
					/* This means the scene (except scene) wasn't at top and Focus() needs to be called */
					(*it)->Focus();
				}
				//The reason we use iterator is that if Exit modifies the vector, it will be invalid, which is good.
				for(auto it2 = stack.begin(); it2 != stack.end(); ++it2){
					if( it2 == it ){
						//Don't call exit on the except scene.
						continue;
					}
					(*it2)->Exit();
				}
			}else{
				//The reason we use iterator is that if Exit modifies the vector, it will be invalid, which is good.
				for(auto it = stack.begin(); it != stack.end(); ++it){
					(*it)->Exit();
				}
			}
			
			stack.clear();
			if( except_scene.empty() == false ){
				stack.push_back(scenes[except_scene]);
			}
			stackHasChanged = true;			
		}

		void EApplication::Run(){
			/* See SDLLib:ShowWindow().h for explanation */
			sdl->ShowWindow();
			
			bool quit = false;
			SDL_Event e;

			std::vector<EScenePTR> tempStack;
			tempStack.reserve(EAPP_MAXSTACK);
			
			std::vector<EScenePTR> tempEntering;
			tempEntering.reserve(EAPP_MAXSTACK);
			
			const bool _vsync = vsync;
			Uint32 total_frame_ms = 0; //This is used when vsync is off
			const Uint32 _targetTimePerFrame = timePerFrame; //16 for 60fps
			
			/* start is also used to cap the framerate when vsync is off */
			Uint32 start = 0;
			Uint32 old_start = 0;
			
			//160ms which equals to roughly 10 updates max.
			const Uint32 max_delta = maxUpdatesToCatchUp * _targetTimePerFrame;
			printf("[EApplication] max_delta = %d\n", max_delta);
			//Delta is the elapsed time since the last => (SDL_GetTicks())
			Uint32 delta = 0;
			Uint32 accumulated_delta = 0;
			
#ifdef EAPPLICATION_PAUSEFRAME
			bool pause_frame = false;
			const int frames_per_key = 3;
			int current_frame = 0;
			Uint32 paused_time = 0;
#endif

			debug->l("[EApplication] Loop begins...\n\n");
			old_start = SDL_GetTicks();
			while(!quit){
#ifdef EAPPLICATION_PAUSEFRAME
				paused_time = 0;
				if( pause_frame ){
					//First grabs value then increments, so... we actually wait the for the actual frame to complete.
					if( current_frame++ >= frames_per_key ){
						current_frame = 1;
						printf("-- Frame is paused, please press enter to continue...");
						paused_time = SDL_GetTicks();
						getchar();
						paused_time = SDL_GetTicks() - paused_time;
					}
				}
#endif
				//We need to make sure "start" is not modified after this so that there isn't a delay in vsync if we are behind.
				/* The reason this is after `pause_frame` is because, it is easier to deal with the paused time at the start of the frame rather then
				 *  . on the next frame. Because sure, if start is first, delta will have 16ms but the next frame will have the paused time so would have to substract on the next frame */
				start = SDL_GetTicks();
#ifdef EAPPLICATION_PAUSEFRAME
				/* Instead of substracting on `start`, we substract it in delta, making delta value the correct one. */
				delta = (start - old_start) - paused_time;
#else
				delta = start - old_start;
#endif
				old_start = start;
				//Cap delta time
				if( delta > max_delta ){
					/* I'm not sure how to explain why we don't need to modify start 
					 *  . The next delta will the correct time (how long it took to go through the whole loop) */
					delta = max_delta;
				}
				
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
					
					/* We consult the input every catch up, in order to be more responsive when lagging */
					while( SDL_PollEvent(&e) != 0 ){
						if( e.type == SDL_QUIT ){
							quit = true;
						}else if( e.type == SDL_KEYDOWN ){
#ifdef EAPPLICATION_PAUSEFRAME
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
						tempStack = stack;
					}
					/* This has to be before any scene function because it updates TimeManager */
					this->Update(delta);
					/* The reason this is after tempStack is because if Enter stacks a scene, it will "queue" the enter function but call Update first.
					 * In this order, first copies the tempStack then Enter and Update function will be called in the correct order. */
					if( entering.size() > 0 ){
						printf("[EApplication] Enter\n");
						//Basically, Enter() is like an early Update. I have decided it's okay to stack inside Enter as well (only Update and Enter)
						tempEntering.swap(entering); //`entering` will be empty.
						for(unsigned int i = 0; i < tempEntering.size(); ++i){
							tempEntering[i]->Enter();
						}
						tempEntering.clear();
					}
					for(unsigned int i = 0; i < tempStack.size(); i++){
						tempStack[i]->Update();
					}

				}while(accumulated_delta >= _targetTimePerFrame);
				
				sdl->Clear();
				for(unsigned int i = 0; i < tempStack.size(); i++){
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