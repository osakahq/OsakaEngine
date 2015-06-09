 #include "stdafx.h"

#ifndef COMPONENT_EVENTHANDLER_H
#define COMPONENT_EVENTHANDLER_H

namespace Osaka{
	namespace Component{
		class EventArgs;
		/* Note:
		 *  - uintptr_t was a hack.
		 *
		 * TODO: 
		 *	- Maybe add a return value when the functions are called to know if they wanna be automatically unhooked */

		/* Source: http://stackoverflow.com/questions/14189440/c-class-member-callback-simple-examples
		 * Usage:
		 *  - class: 
		 * 		- eventhandler->add(this, std::bind(&MyClass::Callback, this, std::placeholders::_1));
		 *  - static function (free functions): 
		 * 		- eventhandler->addHandler([](int x) { std::cout << "x is " << x << '\n'; });
		 * 		- eventhandler->addHandler(freeStandingCallback); 
		 * */
		class EventHandler
		{
		private:
			std::unordered_map<int, std::function<void(EventArgs&)>> map;

			CRITICAL_SECTION criticalSection;
		public:

			EventHandler();
			~EventHandler();
			void Raise(EventArgs& e);

			void Hook(int id, std::function<void(EventArgs&)> callback);
			void Unhook(int id);
		};
	}
}
#endif