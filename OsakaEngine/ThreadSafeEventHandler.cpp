 #include "stdafx.h"
#include "ConsoleColors.h"
#include "ThreadSafeEventRegistree.h"
#include "EventArgs.h"
#include "ThreadSafeEventHandler.h"

namespace Osaka{
	namespace Component{
		ThreadSafeEventHandler::ThreadSafeEventHandler(){
			InitializeCriticalSection(&this->criticalSection);
		}
		ThreadSafeEventHandler::~ThreadSafeEventHandler(){
			EnterCriticalSection(&this->criticalSection);
			for(unsigned int i = 0; i < events.size(); ++i){
				events[i]->__EventHandler_Deattach();
			}
			events.clear();
			LeaveCriticalSection(&this->criticalSection);
			DeleteCriticalSection(&this->criticalSection);
		}

		void ThreadSafeEventHandler::Raise(EventArgs& e){
			EnterCriticalSection(&this->criticalSection);
			for(unsigned int i = 0; i < events.size(); ++i){
				events[i]->CallFunc(e);
			}
			LeaveCriticalSection(&this->criticalSection);
		}
		
		void ThreadSafeEventHandler::Hook(ThreadSafeEventRegistree* e, std::function<void(EventArgs&)> callback, bool _throw){
			//Default _throw = false
			EnterCriticalSection(&this->criticalSection);
			e->SetFunc(callback);
			e->__EventHandler_Attach(this, _throw);
			events.push_back(e);
			LeaveCriticalSection(&this->criticalSection);
		}
		
		void ThreadSafeEventHandler::__Event_Unhook(ThreadSafeEventRegistree* e){
			//Called from Event
			EnterCriticalSection(&this->criticalSection);
			auto it = std::find(events.begin(), events.end(), e);
			if( it == events.end() ){
				throw std::exception("[EventHandler] Unhook -> Event doesn't exist");
			}
			//No need. Event sets `ref` to NULL
			//e->Deattach();
			events.erase(it);
			LeaveCriticalSection(&this->criticalSection);
		}
	}
}