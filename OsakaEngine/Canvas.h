 #include "stdafx.h"
#ifndef RPGLIB_CANVAS_H
#define RPGLIB_CANVAS_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{

		class Canvas{
		public:
			Canvas(SDL_Renderer* raw_renderer, RulerPTR& ruler);
			virtual ~Canvas();
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

			virtual void Update() = 0;
			virtual void Draw() = 0;

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner. Raw */
			SDL_Renderer* raw_renderer;
			/* NOT Owner. Layer parent. */
			LayerPTR layer_parent;
			/* NOT Owner */
			RulerPTR ruler;
		};
	}
}
#endif