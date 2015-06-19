 #include "stdafx.h"

#ifndef COMPONENT_THREADSAFEEVENTREGISTREE_H
#define COMPONENT_THREADSAFEEVENTREGISTREE_H

namespace Osaka{
	namespace Component{
		class EventArgs;
		class ThreadSafeEventHandler;
		
		class ThreadSafeEventRegistree
		{
		private:
			ThreadSafeEventHandler* eventhandler;
			CRITICAL_SECTION criticalSection;
			std::function<void(EventArgs&)> func;

			/* When calling Unhook it will set this false so that if a Raise action is going on, it won't call the callback. */
			volatile bool deattaching;
			volatile bool deleting;
		public:
			/* Gives away ownership */
			static ThreadSafeEventRegistree* CreateRawEvent(){
				//If I need to override this function then, I should have like a global EventBuilder var.
				return new ThreadSafeEventRegistree();
			}

			ThreadSafeEventRegistree();
			~ThreadSafeEventRegistree();

			
			void Call(EventArgs& args);

			void Register(ThreadSafeEventHandler* eventhandler, std::function<void(EventArgs&)> callback);

			/* Call this if you need to manually unhook */
			void Unregister();
			/* Called from Registry when Registry is being deleted. */
			void __Registry_Deattach();
		};
	}
}
#endif