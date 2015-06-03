 #include "stdafx.h"
#ifndef RPGLIB_GAMESESSION_H
#define RPGLIB_GAMESESSION_H
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class GameSession{
		public:
			GameSession();
			~GameSession();
			void _delete();
			//Owner
			//Character* character;
			//Party* party;
			//GameVars* vars;
			//Storage* storage;

		/* ----------------------------------------------------------------------------------- */
		private:
			
		};
	}
}
#endif