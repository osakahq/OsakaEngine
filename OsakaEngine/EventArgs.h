 #include "stdafx.h"
#ifndef COMPONENT_EVENTARGS_H
#define COMPONENT_EVENTARGS_H

namespace Osaka{
	namespace Component{
		//See RecieveEventArgs for your custom EventArgs
		class EventArgs
		{
	
		public:
			/* No raw pointer. */
			static EventArgs CreateEmptyArgs(){
				return EventArgs();
			}
			EventArgs(){
				auto_unregister = false;
			}
			virtual ~EventArgs(){

			}

			bool auto_unregister;
		};

	}
}
#endif
