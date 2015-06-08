#include "stdafx.h"
#ifndef RPGLIB_GAMESESSIONMANAGER_H
#define RPGLIB_GAMESESSIONMANAGER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/* You can have different game sessions. Example: FF8 Laguna and company */
		class GameSessionManager{
		public:
			GameSessionManager(GameDataPTR& data);
			~GameSessionManager();
			void _delete();
			void InsertSession(std::string name, GameSessionPTR& session);

			/*************************************************************************/
			//I moved these functions from RPGFactory to here
			/* Gives away ownership. 
			 * It creates the sample gamesessions for newgame (acquired from the data game file) */
			GameSessionManagerPTR CreateGameSessionManagerFromGameData();
			/* Gives away ownership. 
			 * This functions is to load games. */
			GameSessionManagerPTR CreateGameSessionManager(unorderedmap_gamesession_dataPTR& gamesessions);
			/* Gives away onwership.
			 * This is used to save games */
			unorderedmap_gamesession_dataPTR CreateGameSessionStructs(GameSessionManagerPTR& gsm);
			/* This function was on Private, Gives away ownership. 
			 * I'm not sure if this goes here of factory */
			GameSessionPTR CreateGameSession(gamesession_dataPTR& session);
			/*************************************************************************/
		/* ----------------------------------------------------------------------------------- */
		private:
			//OWNER of all GameSessions and the map sessions
			std::unordered_map<std::string, GameSessionPTR> sessions;

			/* NOT Owner. This was in RPGFactory. GameData ownership is in RPGApplication */
			GameDataPTR data;
		};
	}
}
#endif