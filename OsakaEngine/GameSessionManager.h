#include "stdafx.h"
#ifndef RPGLIB_GAMESESSIONMANAGER_H
#define RPGLIB_GAMESESSIONMANAGER_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/* You can have different game sessions. Example: FF8 Laguna and company */
		class GameSessionManager{
		public:
			GameSessionManager();
			~GameSessionManager();
			void _delete();
			void InsertSession(std::string name, GameSessionPTR& session);
		/* ----------------------------------------------------------------------------------- */
		private:
			//OWNER of all GameSessions and the map sessions
			std::unordered_map<std::string, GameSessionPTR> sessions;
		};
	}
}
#endif