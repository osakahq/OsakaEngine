#include "stdafx.h"
#include "GameSession.h"
#include "GameSessionManager.h"
namespace Osaka{
	namespace RPGLib{
		GameSessionManager::GameSessionManager(){

		}
		GameSessionManager::~GameSessionManager(){
#ifdef _DEBUG
			_CHECKDELETE("GameSessionManager");
#endif
		}
		void GameSessionManager::_delete(){
			for(auto it = sessions.begin(); it != sessions.end(); ++it )
				it->second->_delete();
			sessions.clear();
		}

		/* Only called from Factory */
		void GameSessionManager::InsertSession(std::string name, GameSessionPTR& session){
			/* Takes ownership */
			sessions[name] = session;
		}
	}
}