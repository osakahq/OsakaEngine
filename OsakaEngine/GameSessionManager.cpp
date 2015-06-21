#include "stdafx.h"

#include "GameData.h"
#include "GameSession.h"
#include "GameSessionManager.h"
namespace Osaka{
	namespace RPGLib{
		GameSessionManager::GameSessionManager(GameData* data){
			this->data = data;
		}
		GameSessionManager::~GameSessionManager(){
#ifdef _DEBUG
			_CHECKDELETE("GameSessionManager");
#endif
			data = NULL;
			for(auto it = sessions.begin(); it != sessions.end(); ++it )
				delete it->second;
			sessions.clear();
		}
		
		/* Only called from Factory */
		void GameSessionManager::InsertSession(const std::string& name, GameSession* session){
			/* Takes ownership */
			sessions[name] = session;
		}

		GameSession* GameSessionManager::CreateGameSession(gamesession_data& session){
			//TODO: I'm not sure if this goes here of factory
			GameSession* gs = new GameSession();
			//debug->l("[RPGFactory] TODO CREATEGAMESESSION");
			LOG("[RPGFactory] TODO CREATEGAMESESSION\n");
			return gs;
		}
		GameSessionManager* GameSessionManager::CreateGameSessionManagerFromGameData(){
			/* TODO: Creo que necesito crear SessionManager, GameSessionManager maneja SessionManager el cual tiene las sesiones del juego.
			 * Las sesiones sirve por ejemplo: FF8, cuando esta en la historia principal pero esta la historia de Lagoon. */

			//--GameSessionManagerPTR gsm = std::make_shared<GameSessionManager>();
			
			//For each gamesession in the XML data file (game-sessions node)
			//--for( auto it = data->gamesessions->begin(); it != data->gamesessions->end(); ++it ){
				//We have the struct data so we only need to create the GameSession class from it
			//--	gsm->InsertSession(it->first, this->CreateGameSession(it->second));
			//--}
			
			//--return gsm;
			LOG("[RPGFactory] TODO CreateGameSessionManagerFromGameData\n");
			return NULL;
		}
	}
}