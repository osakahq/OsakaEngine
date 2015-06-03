#include "stdafx.h"

#include "GameData.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "Debug.h"
#include "RPGFactory.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGFactory::RPGFactory(Debug::DebugPTR& debug, GameDataPTR& data){
			this->debug = debug;
			this->data = data;
		}
		RPGFactory::~RPGFactory(){
			
		}
		void RPGFactory::_delete(){
			debug = nullptr;
			data = nullptr;
		}
		GameSessionPTR RPGFactory::CreateGameSession(gamesession_dataPTR& session){
			GameSessionPTR gs = std::make_shared<GameSession>();
			debug->l("[RPGFactory] TODO CREATEGAMESESSION");
			return gs;
		}
		GameSessionManagerPTR RPGFactory::CreateGameSessionManagerFromGameData(){
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