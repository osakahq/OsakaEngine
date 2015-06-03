 #include "stdafx.h"
#ifndef COMPONENT_EVENTARGS_H
#define COMPONENT_EVENTARGS_H

namespace Osaka{
	namespace Component{
		//See RecieveEventArgs for your custom EventArgs
		class EventArgs
		{
	
		public:
			EventArgs();
			//~EventArgs();
		};

		//Empty Event Args
		//For extern to work it also needs the implemantation in cpp
		//Source: http://stackoverflow.com/questions/19929681/c-global-variable-declaration
		extern EventArgs EmptyEventArgs;
	}
}
#endif
