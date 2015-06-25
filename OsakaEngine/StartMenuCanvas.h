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
			
			void Init(Layer* layer_parent, RPGScene* scene_parent, Script* script, SceneScript* mainscript) override;
			void Load(RPGFactory& factory) override;
			void Unload() override;
			void Ready() override;
			void Enter() override;
			void Update(Engine::keyboard_state& state) override;
			void Draw() override;
		private:
			Timer* timer;
			bool added_subtitle_effect;

			Image* background;
			Image* title;
			Image* subtitle;

			FloatingEffect* effect;
			FadeInEffect* fadein;
		};
	}
}

#endif