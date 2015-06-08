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
		
	}
}