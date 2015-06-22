#include "stdafx.h"
#ifndef RPGLIB_USERINTERFACE_H
#define RPGLIB_USERINTERFACE_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class UserInterface{
		public:
			UserInterface(SDL_Renderer* raw_renderer, Ruler* ruler);
			virtual ~UserInterface();
			
			virtual void Init(Layer* layer_parent);

			virtual void Load(RPGFactory& factory);
			virtual void Unload();

			virtual void Enter();
			virtual void Ready();
			virtual void Exit();

			virtual void Show();
			virtual void StandBy();
			virtual void Focus();

			virtual void Update();
			virtual void Draw();

			virtual void End();
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner. Layer parent */
			Layer* layer_parent;
			/* NOT Owner. Raw */
			SDL_Renderer* raw_renderer;
			/* NOT Owner */
			Ruler* ruler;
		};
	}
}
#endif