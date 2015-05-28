 #include "stdafx.h"
#ifndef RPGLIB_LAYER_H
#define RPGLIB_LAYER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/* This class goes into RPGScene stack(loop). This is also the "script" of the layer. */
		class Layer{
		public:
			Layer(std::string id, RPGApplicationPTR& app, RPGScenePTR& parent, CanvasPTR& canvas, UserInterfacePTR& ui);
			virtual ~Layer();
			virtual void _delete();
			
			virtual void Load();
			virtual void Unload();

			/* When entering the stack(vector) in RPGScene */
			virtual void Ready(LayerArgsPTR& args);
			/* When the layer exits the loop. This is always called if the layer was in stack when scene is exited. */
			virtual void Exit();

			/* Mainly only used to set the variables focus, standby. */
			virtual void Show();	//When just entering the stack and has focus
			virtual void StandBy(); //Already or just entering the stack and doesn't have focus.
			virtual void Focus();	//When already in stack and regained focus

			void Update();
			void Draw();

			std::string id;
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplicationPTR app;

			/* Owner */
			CanvasPTR canvas;
			/* Owner */
			UserInterfacePTR ui;

			/* NOT Owner */
			RPGScenePTR parent;

			bool focus;
			bool standby;
			bool instack;
			bool hidden;

			void StandByHide(bool val);
			/* The reason there is a special `UpdateEx()` is to not worry about copying the code inside `Update()` */
			virtual void UpdateEx(); //This is where the code goes (script)
		};
	}
}
#endif