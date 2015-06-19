 #include "stdafx.h"
#include "ConsoleColors.h"
#include "ThreadSafeEventRegistree.h"
#include "EventArgs.h"
#include "ThreadSafeEventHandler.h"

namespace Osaka{
	namespace Component{
		ThreadSafeEventHandler::ThreadSafeEventHandler(){
			InitializeCriticalSection(&this->criticalSection);
			deleting = false;
		}
		ThreadSafeEventHandler::~ThreadSafeEventHandler(){
			deleting = true;
			EnterCriticalSection(&this->criticalSection);
			for(unsigned int i = 0; i < events.size(); ++i){
				events[i]->__Registry_Deattach();
			}
			events.clear();
			LeaveCriticalSection(&this->criticalSection);
			DeleteCriticalSection(&this->criticalSection);
		}

		void ThreadSafeEventHandler::Raise(EventArgs& e){
			if( deleting ) return;
			EnterCriticalSection(&this->criticalSection);
			for(unsigned int i = 0; i < events.size(); ++i){
				events[i]->Call(e);
				if( e.auto_unregister ){
					remove_queue.push_back(i);
				}
			}
			if( !remove_queue.empty() ){
				__AutoRemove();
			}
			LeaveCriticalSection(&this->criticalSection);
		}
		void ThreadSafeEventHandler::__AutoRemove(){
			//This is only called in raise so don't add CriticalSection
			for(unsigned int i = 0; i < remove_queue.size(); ++i){
				events[remove_queue[i]]->__Registry_Deattach();
				events.erase(events.begin()+i);
			}
			remove_queue.clear();
		}

		void ThreadSafeEventHandler::__Registree_Attach(ThreadSafeEventRegistree* e, std::function<void(EventArgs&)>& callback){
			if( deleting ) return;
			EnterCriticalSection(&this->criticalSection);
			auto it = std::find(events.begin(), events.end(), e);
			if( it != events.end() ){
				(*it)->__Registry_Deattach();
				events.erase(it);
			}
			events.push_back(e);
			LeaveCriticalSection(&this->criticalSection);
		}
		
		void ThreadSafeEventHandler::__Registree_Deattach(ThreadSafeEventRegistree* e){
			if( deleting ) return;
			EnterCriticalSection(&this->criticalSection);
			auto it = std::find(events.begin(), events.end(), e);
			if( it != events.end() ){
				//Called from Registree
				/* The reason we don't need to check anything is because this is different than attach.
				 * If were are replacing an id, we must make sure to announce to deattach it. */
				events.erase(it);
			}
			LeaveCriticalSection(&this->criticalSection);
		}

	}
}