#include "stdafx.h"
#ifndef RPGLIB_USERINTERFACE_H
#define RPGLIB_USERINTERFACE_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class UserInterface{
		public:
			UserInterface(SDL_Renderer* raw_renderer, RulerPTR& ruler);
			virtual ~UserInterface();
			virtual void _delete();
			virtual void Init(LayerPTR& layer_parent);

			virtual void Load();
			virtual void Unload();

			virtual void Enter();
			virtual void Ready();
			virtual void Exit();

			virtual void Show();
			virtual void StandBy();
			virtual void Focus();

			virtual void Update();
			virtual void Draw();

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner. Layer parent */
			LayerPTR layer_parent;
			/* NOT Owner. Raw */
			SDL_Renderer* raw_renderer;
			/* NOT Owner */
			RulerPTR ruler;
		};
	}
}
#endif