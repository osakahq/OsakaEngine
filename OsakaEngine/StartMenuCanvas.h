 #include "stdafx.h"

#ifndef RPGLIB_STARTMENUCANVAS_H
#define RPGLIB_STARTMENUCANVAS_H
#include "Canvas.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class StartMenuCanvas : public Canvas{
		public:
			StartMenuCanvas(SDL_Renderer* raw_renderer, Ruler* ruler);
			~StartMenuCanvas();
			
			void Update() override;
			void Draw() override;
		private:
			
		};
	}
}

#endif