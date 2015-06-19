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
			bool volatile deleting;
			/* NOT Owner of Event* */
			std::vector<ThreadSafeEventRegistree*> events;
			/* int is the position. */
			std::vector<int> remove_queue;

			CRITICAL_SECTION criticalSection;

			void __AutoRemove();
		public:

			ThreadSafeEventHandler();
			~ThreadSafeEventHandler();
			void Raise(EventArgs& e);

			/* Called from EventRegistree */
			void __Registree_Attach(ThreadSafeEventRegistree* e, std::function<void(EventArgs&)>& callback);
			/* Called from EventRegistree when Registree is being deleted */
			void __Registree_Deattach(ThreadSafeEventRegistree* e);
		};
	}
}
#endif