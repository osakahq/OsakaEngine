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

			/* This is called from Effect (OneLoop) */
			virtual void OnFadeInOneLoop(Component::EventArgs& e);
		private:
			Timer* timer;
			
			Square* white_background;
			Image* background;
			Image* title;
			Image* subtitle;

			FloatingEffect* effect;
			FadeInEffect* fadein;

			/* 0 = fade in start background.
			 * 1 = fade in start title */
			int phase;
		};
	}
}

#endif