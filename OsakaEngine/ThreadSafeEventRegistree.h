 #include "stdafx.h"

#ifndef COMPONENT_THREADSAFEEVENT_H
#define COMPONENT_THREADSAFEEVENT_H

namespace Osaka{
	namespace Component{
		class EventArgs;
		class ThreadSafeEventHandler;
		
		class ThreadSafeEventRegistree
		{
		private:
			ThreadSafeEventHandler* ref;
			CRITICAL_SECTION criticalSection;
			std::function<void(EventArgs&)> func;
		public:
			static ThreadSafeEventRegistree* CreateRawEvent(){
				//If I need to override this function then, I should have like a global EventBuilder var.
				return new ThreadSafeEventRegistree();
			}

			ThreadSafeEventRegistree();
			~ThreadSafeEventRegistree();

			void SetFunc(std::function<void(EventArgs&)> func);
			/* When calling Unhook it will set this false so that if a Raise action is going on, it won't call the callback. */
			volatile bool deattaching;
			void CallFunc(EventArgs& args);

			/* OPTIONAL. This can be called by the owner, if you want to manually unhook
			 * ~destructor will call this function if ref is not NULL */
			void Unhook();

			/* This is called by the EventHandler */
			void __EventHandler_Attach(ThreadSafeEventHandler* ref, bool _throw);
			/* This is called from EventHandler */
			void __EventHandler_Deattach();
		};
	}
}
#endif