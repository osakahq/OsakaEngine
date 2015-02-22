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

			/* Gives away ownership. 
			 * It creates the sample gamesessions for newgame (acquired from the data game file) */
			GameSessionManagerPTR CreateGameSessionManagerFromGameData();
			/* Gives away ownership. 
			 * This functions is to load games. */
			GameSessionManagerPTR CreateGameSessionManager(unorderedmap_gamesession_dataPTR& gamesessions);
			/* Gives away onwership.
			 * This is used to save games */
			unorderedmap_gamesession_dataPTR CreateGameSessionStructs(GameSessionManagerPTR& gsm);
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner. GameData ownership is in RPGApplication */
			GameDataPTR data;

			/* Gives away ownership. */
			GameSessionPTR CreateGameSession(gamesession_dataPTR& session);

			/* NOT Owner. */
			Debug::DebugPTR debug;
		};
	}
}
#endif