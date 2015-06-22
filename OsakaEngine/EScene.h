 #include "stdafx.h"
#ifndef ENGINE_ESCENE_H
#define ENGINE_ESCENE_H
#include "osaka_forward.h"
namespace Osaka{
	namespace Engine{
		
		class EScene{
		public:

			/* This is so that the derived class deconstructor is called. */
			virtual ~EScene(){};
			
			/* This is to announce the loop is about to start. */
			virtual void Start() = 0;
			/* Load functions server the purpose of creating the classes, everything that the scene needs.
			 * This function is called from AssetManager (loading thread) */
			virtual void Load() = 0;
			/* This function is to destroy the objects created (not assets). 
			 * Called from AssetManager (loading thread) */
			virtual void Unload() = 0;

			/* Called when the scene is removed from the stack */
			virtual void Exit() = 0;

			/* Entering the loop (FirstUpdate) */
			virtual void Enter() = 0;
			/* Called when the scene is added to the stack and when the scene has just been stacked but doesn't have initial focus
			 * params is deleted by the callee. */
			virtual void ReadyStandBy(ESceneArgs& params) = 0;
			/* Called when the scene is added to the stack and when the scene has just been stacked and is on top of the stack (has focus)
			 * params is deleted by the callee */
			virtual void ReadyShow(ESceneArgs& params) = 0;
			/* Called when the scene is *no longer* on top of the stack (already in stack) */
			virtual void StandBy() = 0;
			/* Called when the scene is BACK on top of the stack (already in stack) */
			virtual void Focus() = 0;

			virtual void Update(keyboard_state& state) = 0;
			virtual void Draw() = 0;

			/* Called when the application is closing... */
			virtual void End() = 0;

			/* This is used in EApplication */
			virtual std::string GetId() = 0;
		private:
			
		};
	}
}
#endif