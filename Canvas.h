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
			virtual void Load() = 0;
			virtual void Unload() = 0;
			virtual void Show() = 0;
			virtual void Hide() = 0;
			virtual void StandBy() = 0;
			virtual void Focus() = 0;
			virtual void Update() = 0;
			virtual void Draw() = 0;

			virtual void Reset() = 0;
		/* ----------------------------------------------------------------------------------- */
		protected:
			/* NOT Owner */
			RPGApplicationPTR app;
		};
	}
}
#endif