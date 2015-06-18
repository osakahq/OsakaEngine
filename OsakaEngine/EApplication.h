 #include "stdafx.h"
#ifndef ENGINE_EAPPLICATION_H
#define ENGINE_EAPPLICATION_H
#include "osaka_forward.h"
#define EAPP_MAXSTACK 20

namespace Osaka{
	
	namespace Engine{
		
		class EApplication{
		public:
			EApplication(Debug::Debug* d, SDLLib* sdl, IFileLoader* fileloader);
			virtual ~EApplication();
			
			/* NOT Owner. debug always has to be set because the basic function is to log. And even in production you need to log. */
			Debug::Debug* debug;
			/* Owner. The main functions of SDL */
			SDLLib* sdl;

			/* */
			virtual void Init(bool vsync, int timePerFrame, int maxUpdatesToCatchUp);
			/* Takes owner ship of the scene */
			void AddScene(const std::string& id, EScene* scene);
			/* Class a scene load function. Called from AssetManager (loading thread) */
			virtual void CallLoad(const std::string& id);
			virtual void CallUnload(const std::string& id);

			virtual void Update(const Uint32 delta) = 0;
			
			virtual void BeforePresent() = 0;
			virtual void AfterPresent(const Uint32 started) = 0;

			/* This is the main loop. */
			virtual void Run();
			/* When the loop exits */
			virtual void End() = 0;

			// EScenePassParams it is used to pass a param to the soon to be actived scene
			// For scenes to communicate, the caller scene should bind a callback in EScenePassParams or the other solution written in the notes.
			/* Makes a transition to switch scene. It removes all scenes from the stack. */
			void Switch(const std::string& scene, ESceneArgs& in_param);
			/* Instead of transition, it is superimposed on the current scene. This means no loading scene. */
			void Stack(const std::string& scene, ESceneArgs& in_param);
			/* Stacks an scene to the bottom of the stack */
			void BottomStack(const std::string& scene, ESceneArgs& in_param);
			/* Removes a scene from the stack */
			void Remove(const std::string& scene);
			/* Removes all scenes from the stack */
			void RemoveAllFromStack(const std::string& except_scene = "");

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* Owner. This class is the owner of the scenes. So, it is its responsability to delete them
			 * All other vector/arrays that use the raw pointer, its fine because the scenes won't be deleted but in `_delete` */
			std::unordered_map<std::string, EScene*> raw_scenes;
			
			/* With the benchmarks I did and because loop calls > copy calls, it's better to copy vector to array and the loop it
			 * In release mode, copying vector to array is extremely fast. See the benchmark.*/
			/* This array is like a workspace. Use this array to copy and loop instead of using vector iterators (Slow) */
			EScene* copy_stack[EAPP_MAXSTACK];

			/* Owner. Strategy pattern to load directly from file or with PhysicsFS */
			IFileLoader* fileloader;
			
			/* Owner of the stack. Scenes are in the `scenes` variable */
			std::vector<EScene*> stack;
			/* Even though is a vector, we still need this variable. This is used to not copy the stack every loop */
			bool stackHasChanged;

			/* This is a list of the scenes that are just entering the stack */
			std::vector<EScene*> entering;

			/* If vsync is off then we cap the framerate */
			bool vsync;
			/* If vsync is true, fps is ignored. */
			int timePerFrame;
			/* This number is multiplied with timePerFrame. That number will be the maximum time for delta  */
			int maxUpdatesToCatchUp;
		};
	}
}
#endif