 #include "stdafx.h"
#ifndef RPGLIB_RPGLIBINCLUDE_H
#define RPGLIB_RPGLIBINCLUDE_H

namespace Osaka{
	namespace RPGLib{
		struct TransitionType{
			TransitionType(){}
			enum Value{
				SWITCH, STACK	
			};
		};
	}
}

#endif