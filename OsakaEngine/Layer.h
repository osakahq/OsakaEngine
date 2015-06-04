 #include "stdafx.h"
#ifndef RPGLIB_LAYER_H
#define RPGLIB_LAYER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/* This class goes into RPGScene stack(loop). This is also the "script" of the layer. */
		class Layer{
		public:
			Layer(std::string id, ScriptPTR& script, CanvasPTR& canvas, UserInterfacePTR& ui);
			virtual ~Layer();
			virtual void _delete();
			
			virtual void Init(RPGApplicationPTR& app);
			virtual void Load();
			virtual void Unload();

			/* When entering the stack(vector) in RPGScene
			 * If you modify this, remember there is OneLayer that completely overrides this function (ready) */
			void Ready(LayerArgsPTR& args);
			/* When the layer exits the loop. This is always called if the layer was in stack when scene is exited. */
			void Exit();

			/* Mainly only used to set the variables focus, standby. */
			void Show();	//When just entering the stack and has focus
			void StandBy(); //Already or just entering the stack and doesn't have focus.
			void Focus();	//When already in stack and regained focus

			void Update();
			void Draw();
			void End();
			std::string id;

			/* NOT Owner. The reason Layer has `app` is because Canvas/UI might need debug or other unforseen dependencies */
			RPGApplicationPTR app;
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* Owner */
			ScriptPTR script;
			/* Owner */
			CanvasPTR canvas;
			/* Owner */
			UserInterfacePTR ui;

			bool focus;
			bool standby;
			bool instack;
			bool hidden;

			void StandByHide(bool val);
		};
	}
}
#endif