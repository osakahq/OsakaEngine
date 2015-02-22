#include "stdafx.h"
#ifndef ENGINE_EAPPLICATION_H
#define ENGINE_EAPPLICATION_H
#include "osaka_forward.h"
#define EAPP_MAXSTACK 99

namespace Osaka{
	
	namespace Engine{
		
		class EApplication{
		public:
			EApplication(Debug::DebugPTR& d, SDLLibPTR& sdl, IFileLoaderPTR& fileloader);
			virtual ~EApplication();
			virtual void _delete();
			/* NOT Owner. debug always has to be set because the basic function is to log. And even in production you need to log. */
			Debug::DebugPTR debug;
			
			/* */
			void Init();
			/* Takes owner ship of the scene */
			void AddScene(std::string id, EScenePTR& scene);

			/* In case the derived class wants to run some code every update */
			virtual void Update();
			/* This is the main loop. */
			virtual void Run();

			// EScenePassParams it is used to pass a param to the soon to be actived scene
			// For scenes to communicate, the caller scene should bind a callback in EScenePassParams or the other solution written in the notes.
			/* Makes a transition to switch scene. It removes all scenes from the stack. */
			void Switch(const char* scene, EScenePassParamsPTR& in_param);
			/* Instead of transition, it is superimposed on the current scene. This means no loading scene. */
			void Stack(const char* scene, EScenePassParamsPTR& in_param);
			/* Stacks an scene to the bottom of the stack */
			void BottomStack(const char* scene, EScenePassParamsPTR& in_param);
			/* Removes a scene from the stack */
			void Remove(const char* scene);
			/* Removes all scenes from the stack */
			void RemoveAllFromStack(const char* except_scene = NULL);

		/* ----------------------------------------------------------------------------------- */
		private:
			/* Owner. This class is the owner of the scenes. So, it is its responsability to delete them */
			std::unordered_map<std::string, EScenePTR> scenes;

			/* Owner. The main functions of SDL */
			SDLLibPTR sdl;

			/* Owner. Strategy pattern to load directly from file or with PhysicsFS */
			IFileLoaderPTR fileloader;
			
			/* Owner of the stack. Scenes are in the `scenes` variable */
			std::string stack[EAPP_MAXSTACK];
			int stackItems;
			/* This is used to not copy the stack every loop */
			bool stackHasChanged;
		};
	}
}
#endif