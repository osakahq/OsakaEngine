 #include "stdafx.h"
#include "ConsoleColors.h"
#include "EventArgs.h"
#include "EventHandler.h"

namespace Osaka{
	namespace Component{
		EventHandler::EventHandler(){
			InitializeCriticalSection(&this->criticalSection);
		}
		EventHandler::~EventHandler(){
			map.clear();
			DeleteCriticalSection(&this->criticalSection);
		}

		void EventHandler::Raise(EventArgs& e){
			EnterCriticalSection(&this->criticalSection);
			for(auto i = map.begin(); i != map.end(); ++i){
				(i->second)(e);
			}
			LeaveCriticalSection(&this->criticalSection);
		}
		
		void EventHandler::Hook(int id, std::function<void(EventArgs&)> callback){
			EnterCriticalSection(&this->criticalSection);
			if( map.find(id) == map.end()) {
				map[id] = callback;
			}else{
				throw std::exception("[EventHandler] Hook -> Caller is already registered");
			}
			LeaveCriticalSection(&this->criticalSection);
		}
		
		void EventHandler::Unhook(int id){
			EnterCriticalSection(&this->criticalSection);
			auto it = map.find(id);
			if( it != map.end()) {
				map.erase(it);
			}else{
				throw std::exception("[EventHandler] Unhook -> Caller is not registered");
			}
			LeaveCriticalSection(&this->criticalSection);
		}
	}
}