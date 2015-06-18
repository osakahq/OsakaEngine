#include "stdafx.h"
#include "GameSession.h"
namespace Osaka{
	namespace RPGLib{
		GameSession::GameSession(){

		}
		GameSession::~GameSession(){
#ifdef _DEBUG
			_CHECKDELETE("GameSession");
#endif		
			//delete character;
			//delete party;
			//delete vars;
			//delete storage;
		}
	}
}