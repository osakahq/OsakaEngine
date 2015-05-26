 #include "stdafx.h"
#ifndef RPGLIB_CANVAS_H
#define RPGLIB_CANVAS_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{

		class Canvas{
		public:
			Canvas(RPGApplicationPTR& app);
			virtual ~Canvas();
			virtual void _delete();
			virtual void Init(RPGScenePTR& parent);

			virtual void Load();
			virtual void Unload();

			virtual void Ready();
			virtual void Exit();
			virtual void Show();
			virtual void StandBy();
			virtual void Focus();

			virtual void Update() = 0;
			virtual void Draw() = 0;

		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplicationPTR app;

			/* NOT Owner */
			RPGScenePTR parent;

			/* NOT Owner. Raw */
			SDL_Renderer* raw_renderer;
		};
	}
}
#endif