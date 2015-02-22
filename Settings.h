 #include "stdafx.h"
#ifndef RPGLIB_SETTINGS_H
#define RPGLIB_SETTINGS_H

namespace Osaka{
	namespace RPGLib{
		
		class Settings{
		public:
			Settings(const char* filesettings);
			~Settings();
			void _delete();
		/* ----------------------------------------------------------------------------------- */
		private:
			
		};
	}
}
#endif