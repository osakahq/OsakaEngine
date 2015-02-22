 #include "stdafx.h"
#ifndef ASC_ASCBOOTSTRAP_H
#define ASC_ASCBOOTSTRAP_H
#include "osaka_forward.h"
#include "asc_forward.h"
namespace Osaka{
	namespace Asc{
		AscApplicationPTR asc_bootstrap(const char* filedata, const char* filesettings, Debug::DebugPTR& debug);
	}
}
#endif