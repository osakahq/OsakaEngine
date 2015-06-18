 #include "stdafx.h"
#ifndef RPGLIB_RPGFACTORY_H
#define RPGLIB_RPGFACTORY_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/* This class only creates RPG related classes (Items, Characters, Party) */
		class RPGFactory{
		public:
			RPGFactory(Debug::Debug* debug, GameData* data, GameDataParams* gdp, Factory* factory);
			~RPGFactory();
			void Init();

			/* Gives away ownership */
			Image* CreateImage(const std::string& id_sprite);
			Square* CreateSquare(int x, int y, int h, int w);
			Square* CreateSquare();
			FadeInFadeOutEffect* CreateFadeInFadeOutEffect();

			/* NOT Owner. GameData ownership is in RPGApplication */
			GameData* data;
			/* NOT Owner. Ownership is in RPGApplication */
			GameDataParams* gamedataparams;
			/* NOT Owner */
			Factory* factory;
		private:
			/* NOT Owner. */
			Debug::Debug* debug;

			/* NOT Owner */
			SDL_Renderer* raw_renderer;
		};
	}
}
#endif