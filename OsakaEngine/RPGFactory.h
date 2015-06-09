 #include "stdafx.h"
#ifndef RPGLIB_RPGFACTORY_H
#define RPGLIB_RPGFACTORY_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		struct gamesession_data;

		/* This class only creates RPG related classes (Items, Characters, Party) */
		class RPGFactory{
		public:
			RPGFactory(Debug::DebugPTR& debug, GameDataPTR& data, GameDataParamsPTR& gdp, FactoryPTR& factory);
			~RPGFactory();
			void _delete();
			void Init();

			/* Gives away ownership */
			ImagePTR CreateImage(std::string id_sprite);
			SquarePTR CreateSquare(int x, int y, int h, int w);
			SquarePTR CreateSquare();

			/* NOT Owner. GameData ownership is in RPGApplication */
			GameDataPTR data;
			/* NOT Owner. Ownership is in RPGApplication */
			GameDataParamsPTR gamedataparams;
			/* NOT Owner */
			FactoryPTR factory;
		private:
			/* NOT Owner. */
			Debug::DebugPTR debug;

			/* NOT Owner */
			SDL_Renderer* raw_renderer;
		};
	}
}
#endif