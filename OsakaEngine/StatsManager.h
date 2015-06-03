#include "stdafx.h"
#ifndef RPGLIB_STATSMANAGER_H
#define RPGLIB_STATSMANAGER_H

namespace Osaka{
	namespace RPGLib{
		class Stat;

		class StatsManager{
		public:
			StatsManager();
			~StatsManager();
			
		/* ----------------------------------------------------------------------------------- */
		private:
			std::unordered_map<std::string, Stat> stats;
		};
	}
}
#endif