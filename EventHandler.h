#include "stdafx.h"

#ifndef COMPONENT_EVENTHANDLER_H
#define COMPONENT_EVENTHANDLER_H

namespace Osaka{
	namespace Component{
		class EventArgs;
		/*
		 * - TODO: Maybe add a return value when the functions are called to know if they wanna be automatically unhooked
		*/
		class EventHandler
		{
		private:
			std::unordered_map<uintptr_t, std::function<void(EventArgs&)>> map;

			void _hook(uintptr_t m, std::function<void(EventArgs&)> callback);
			void _unhook(uintptr_t m);

			uintptr_t _concatenate(uintptr_t caller, int modifier);

			CRITICAL_SECTION criticalSection;
		public:

			EventHandler();
			~EventHandler();
			void raise(EventArgs& e);
			//This is just used so that a class can hook multiple times (multiple hooks)
			void m_hook(void* caller, int modifier, std::function<void(EventArgs&)> callback);
			//Source: http://stackoverflow.com/questions/14189440/c-class-member-callback-simple-examples
			//Usage:
			// - class: 
			//		- eventhandler->add(this, std::bind(&MyClass::Callback, this, std::placeholders::_1));
			// - static function (free functions): 
			//		- eventhandler->addHandler([](int x) { std::cout << "x is " << x << '\n'; });
			//		- eventhandler->addHandler(freeStandingCallback);
			void hook(void* caller, std::function<void(EventArgs&)> callback);

			void m_unhook(void* caller, int modifier);
			void unhook(void* caller);
		};
	}
}
#endif