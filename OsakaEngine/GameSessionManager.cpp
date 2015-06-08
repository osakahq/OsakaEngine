#include "stdafx.h"

#include "GameData.h"
#include "GameSession.h"
#include "GameSessionManager.h"
namespace Osaka{
	namespace RPGLib{
		GameSessionManager::GameSessionManager(GameDataPTR& data){
			this->data = data;
		}
		GameSessionManager::~GameSessionManager(){
#ifdef _DEBUG
			_CHECKDELETE("GameSessionManager");
#endif
		}
		void GameSessionManager::_delete(){
			data = nullptr;
			for(auto it = sessions.begin(); it != sessions.end(); ++it )
				it->second->_delete();
			sessions.clear();
		}

		/* Only called from Factory */
		void GameSessionManager::InsertSession(std::string name, GameSessionPTR& session){
			/* Takes ownership */
			sessions[name] = session;
		}

		GameSessionPTR GameSessionManager::CreateGameSession(gamesession_dataPTR& session){
			//TODO: I'm not sure if this goes here of factory
			GameSessionPTR gs = std::make_shared<GameSession>();
			//debug->l("[RPGFactory] TODO CREATEGAMESESSION");
			printf("[RPGFactory] TODO CREATEGAMESESSION\n");
			return gs;
		}
		GameSessionManagerPTR GameSessionManager::CreateGameSessionManagerFromGameData(){
			GameSessionManagerPTR gsm = std::make_shared<GameSessionManager>();
			
			//For each gamesession in the XML data file (game-sessions node)
			for( auto it = data->gamesessions->begin(); it != data->gamesessions->end(); ++it ){
				//We have the struct data so we only need to create the GameSession class from it
				gsm->InsertSession(it->first, this->CreateGameSession(it->second));
			}
			
			return gsm;
		}
	}
}