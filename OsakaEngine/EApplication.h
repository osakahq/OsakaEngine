 #include "stdafx.h"
#ifndef ENGINE_EAPPLICATION_H
#define ENGINE_EAPPLICATION_H
#include "osaka_forward.h"
#define EAPP_MAXSTACK 20

namespace Osaka{
	
	namespace Engine{
		
		class EApplication{
		public:
			EApplication(Debug::DebugPTR& d, SDLLibPTR& sdl, IFileLoaderPTR& fileloader);
			virtual ~EApplication();
			virtual void _delete();

			/* NOT Owner. debug always has to be set because the basic function is to log. And even in production you need to log. */
			Debug::DebugPTR debug;
			/* Owner. The main functions of SDL */
			SDLLibPTR sdl;

			/* */
			virtual void Init(bool vsync, int timePerFrame, int maxUpdatesToCatchUp);
			/* Takes owner ship of the scene */
			void AddScene(std::string id, EScenePTR& scene);
			/* Class a scene load function. Called from AssetManager (loading thread) */
			virtual void CallLoad(std::string id);

			virtual void Update(const Uint32 delta) = 0;
			
			virtual void BeforePresent() = 0;
			virtual void AfterPresent(const Uint32 started) = 0;

			/* This is the main loop. */
			virtual void Run();

			// EScenePassParams it is used to pass a param to the soon to be actived scene
			// For scenes to communicate, the caller scene should bind a callback in EScenePassParams or the other solution written in the notes.
			/* Makes a transition to switch scene. It removes all scenes from the stack. */
			void Switch(const char* scene, ESceneArgsPTR& in_param);
			/* Instead of transition, it is superimposed on the current scene. This means no loading scene. */
			void Stack(const char* scene, ESceneArgsPTR& in_param);
			/* Stacks an scene to the bottom of the stack */
			void BottomStack(const char* scene, ESceneArgsPTR& in_param);
			/* Removes a scene from the stack */
			void Remove(const char* scene);
			/* Removes all scenes from the stack */
			void RemoveAllFromStack(const char* except_scene = NULL);

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* Owner. This class is the owner of the scenes. So, it is its responsability to delete them */
			std::unordered_map<std::string, EScenePTR> scenes;

			/* Owner. Strategy pattern to load directly from file or with PhysicsFS */
			IFileLoaderPTR fileloader;
			
			/* Owner of the stack. Scenes are in the `scenes` variable */
			EScenePTR stack[EAPP_MAXSTACK];
			int stackItems;
			/* This is used to not copy the stack every loop */
			bool stackHasChanged;

			/* This is a list of the scenes that are just entering the stack */
			EScenePTR entering[EAPP_MAXSTACK];
			int enteringItems;

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