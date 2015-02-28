 #include "stdafx.h"
#ifndef ENGINE_ESCENE_H
#define ENGINE_ESCENE_H
#include "osaka_forward.h"
namespace Osaka{
	namespace Engine{
		
		class EScene{
		public:
			//EScene();
			virtual ~EScene(){};
			virtual void _delete() = 0;
			//Constructor and Init are essentially for the same thing: Initializing vars and dependency injection.
			virtual void Init() = 0;
			/* Load functions server the purpose of creating the classes, everything that the scene needs.
			 * This function is called from GameLoader */
			virtual void Load() = 0;
			/* This function is to destroy the objects created (not assets). 
			 * Called from GameLoader */
			virtual void Unload() = 0;

			/* Called when `Switch()/Stack()` functions are called */
			virtual void Show(ESceneArgsPTR& params) = 0;
			/* Called when Remove(scene) or RemoveAllFromStack is called */
			virtual void Hide() = 0;
			/* Called when a new scene is stacked */
			virtual void StandBy() = 0;
			/* When calling BottomStack, it is put at the bottom so it is like Show() but was called to the bottom of the stack */
			virtual void StandBy(ESceneArgsPTR& params) = 0;
			/* This only happens when 2 scenes are stacked, then the top one is `Remove()`ed and the new top scene is called with `Focus()` */
			virtual void Focus() = 0;

			virtual void Update() = 0;
			virtual void Draw() = 0;

			/* This is used in EApplication */
			virtual std::string GetId() = 0;
		private:
			
		};
	}
}
#endif