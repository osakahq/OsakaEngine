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

			/* You only need to override this function when you want a custom EventHandler */
			virtual void Reset(){
				//This is needed because when a Registree wants to unregister, 
				//the next one might not want to do the same.
				auto_unregister = false;
			}

			bool auto_unregister;
		};

	}
}
#endif
