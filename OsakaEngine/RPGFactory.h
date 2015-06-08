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
			RPGFactory(Debug::DebugPTR& debug, GameDataPTR& data);
			~RPGFactory();
			void _delete();
			//void Init();

		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner. GameData ownership is in RPGApplication */
			GameDataPTR data;

			/* NOT Owner. */
			Debug::DebugPTR debug;
		};
	}
}
#endif