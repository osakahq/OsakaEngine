 #include "stdafx.h"
#include "EventArgs.h"
#include "EventHandler.h"

namespace Osaka{
	namespace Component{
		EventHandler::EventHandler(){
			//unordered_map map;
			InitializeCriticalSection(&this->criticalSection);
		}
		EventHandler::~EventHandler(){
			DeleteCriticalSection(&this->criticalSection);
		}

		void EventHandler::raise(EventArgs& e){
			std::unordered_map<uintptr_t, std::function<void(EventArgs&)>>::iterator i;
			EnterCriticalSection(&this->criticalSection);
			for(i = map.begin(); i != map.end(); ++i){
				if( i->second != NULL )
					(i->second)(e);
			}
			LeaveCriticalSection(&this->criticalSection);
		}
		uintptr_t EventHandler::_concatenate(uintptr_t caller, int modifier){
			long lC = caller;
			char bufModifier[6], bufCaller[11];
			_itoa_s(modifier, bufModifier, 10);
			_itoa_s(lC, bufCaller, 10);
	
			char mem[16] = "";
			strcat_s(mem, bufCaller);
			strcat_s(mem, bufModifier);
			long lMem = atol(mem);

			return (uintptr_t)lMem;
		}

		void EventHandler::hook(void* caller, std::function<void(EventArgs&)> callback){
			this->_hook((uintptr_t)caller, callback);
		}
		void EventHandler::m_hook(void* caller, int modifier, std::function<void(EventArgs&)> callback){
			this->_hook(this->_concatenate((uintptr_t)caller, modifier), callback);
		}

		void EventHandler::_hook(uintptr_t m, std::function<void(EventArgs&)> callback){
			EnterCriticalSection(&this->criticalSection);
			std::unordered_map<uintptr_t, std::function<void(EventArgs&)>>::const_iterator exists = map.find(m);
			//Doesn't exists
			if( exists == map.end()) {
				//(uintptr_t)caller is the memory address but in integer format~
				map[m] = callback;
			}else{
				throw std::exception("Caller is already registered");
			}
			LeaveCriticalSection(&this->criticalSection);
		}
		void EventHandler::unhook(void* caller){
			this->_unhook((uintptr_t)caller);
		}
		void EventHandler::m_unhook(void* caller, int modifier){
			this->_unhook(this->_concatenate((uintptr_t)caller, modifier));
		}

		void EventHandler::_unhook(uintptr_t m){
			EnterCriticalSection(&this->criticalSection);
			std::unordered_map<uintptr_t, std::function<void(EventArgs&)>>::const_iterator exists = map.find(m);
			//Exists
			if( exists != map.end()) {
				map.erase(m);
			}else{
#ifdef _DEBUG
				printf("[EventHandler] Unhook -> id does not exist.");
#endif
				//throw std::exception("Caller is not registered");
			}
			LeaveCriticalSection(&this->criticalSection);
		}
	}
}