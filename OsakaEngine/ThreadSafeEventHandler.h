 #include "stdafx.h"

#ifndef COMPONENT_THREADSAFEEVENTHANDLER_H
#define COMPONENT_THREADSAFEEVENTHANDLER_H

namespace Osaka{
	namespace Component{
		class ThreadSafeEventRegistree;
		class EventArgs;
		/* TODO: 
		 *	- Maybe add a return value when the functions are called to know if they wanna be automatically unhooked */

		/* Source: http://stackoverflow.com/questions/14189440/c-class-member-callback-simple-examples
		 * Usage:
		 *  - class: 
		 * 		- eventhandler->add(this, std::bind(&MyClass::Callback, this, std::placeholders::_1));
		 *  - static function (free functions): 
		 * 		- eventhandler->addHandler([](int x) { std::cout << "x is " << x << '\n'; });
		 * 		- eventhandler->addHandler(freeStandingCallback); 
		 * */
		class ThreadSafeEventHandler
		{
		private:
			/* NOT Owner of Event* */
			std::vector<ThreadSafeEventRegistree*> events;
			
			CRITICAL_SECTION criticalSection;
		public:

			ThreadSafeEventHandler();
			~ThreadSafeEventHandler();
			void Raise(EventArgs& e);

			void Hook(ThreadSafeEventRegistree* e, std::function<void(EventArgs&)> callback, bool _throw = false);
			/* Called by Event (coming from manually called from the owner of Event) OR ~destructor */
			void __Event_Unhook(ThreadSafeEventRegistree* e);
		};
	}
}
#endif