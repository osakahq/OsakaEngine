 #include "stdafx.h"
#include "Ruler.h"
#include "SDLLib.h"
#include "Debug.h"
#include "Timer.h"
#include "EventArgs.h"
#include "EventHandler.h"
#include "Canvas.h"
#include "Utils.h"
#include "StartMenuCanvas.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		StartMenuCanvas::StartMenuCanvas(SDL_Renderer* raw_renderer, RulerPTR& ruler) : Canvas(raw_renderer, ruler){
			
		}
		StartMenuCanvas::~StartMenuCanvas(){

		}
		void StartMenuCanvas::_delete(){
			Canvas::_delete();
		}
		void StartMenuCanvas::Update(){
		}
		void StartMenuCanvas::Draw(){
		}
	}
}