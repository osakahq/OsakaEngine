 #include "stdafx.h"
#ifndef RPGLIB_LAYER_H
#define RPGLIB_LAYER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/* This class goes into RPGScene stack(loop). This is also the "script" of the layer. */
		class Layer{
		public:
			/* They are pointers because this class is the Owner of them. */
			Layer(const std::string& _id, Script* script, Canvas* canvas, UserInterface* ui);
			virtual ~Layer();
			
			virtual void Init(RPGApplication* app);
			virtual void Load(RPGFactory& factory);
			virtual void Unload();

			void Enter();
			/* When entering the stack(vector) in RPGScene
			 * If you modify this, remember there is OneLayer that completely overrides this function (ready)
			 * args is deleted by the callee.*/
			void Ready(LayerArgs& args);
			/* When the layer exits the loop. This is always called if the layer was in stack when scene is exited. */
			void Exit();

			/* Mainly only used to set the variables focus, standby. */
			void Show();	//When just entering the stack and has focus
			void StandBy(); //Already or just entering the stack and doesn't have focus.
			void Focus();	//When already in stack and regained focus

			void Update(Engine::keyboard_state& state);
			void Draw();
			void End();
			const std::string id;

			/* NOT Owner. The reason Layer has `app` is because Canvas/UI might need debug or other unforseen dependencies */
			RPGApplication* raw_app;

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* Owner */
			Script* raw_script;
			/* Owner */
			Canvas* raw_canvas;
			/* Owner */
			UserInterface* raw_ui;

			bool focus;
			bool standby;
			bool instack;
			bool hidden;

			void StandByHide(bool val);
		};
	}
}
#endif