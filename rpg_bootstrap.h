 #include "stdafx.h"
#ifndef TESTSUITE_RPGBOOTSTRAP_H
#define TESTSUITE_RPGBOOTSTRAP_H
#include "osaka_forward.h"

namespace Osaka{
	namespace RPGLib{
		RPGApplicationPTR rpg_bootstrap(const char* filedata, const char* filesettings, Debug::DebugPTR& debug);
	}
}
#endif