 #include "stdafx.h"
#include "ThreadSafeEventHandler.h"
#include "ThreadSafeEventRegistree.h"

namespace Osaka{
	namespace Component{
		
		ThreadSafeEventRegistree::ThreadSafeEventRegistree(){
			InitializeCriticalSection(&this->criticalSection);
			eventhandler = NULL;
			deattaching = false;
			deleting = false;
		}
		ThreadSafeEventRegistree::~ThreadSafeEventRegistree(){
			deleting = true;
			EnterCriticalSection(&this->criticalSection);
			if( eventhandler != NULL ){
				eventhandler->__Registree_Deattach(this);
				eventhandler = NULL;
			}
			LeaveCriticalSection(&this->criticalSection);
			DeleteCriticalSection(&this->criticalSection);
		}
		
		void ThreadSafeEventRegistree::Call(EventArgs& args){
			if( deattaching || deleting ) return;
			EnterCriticalSection(&this->criticalSection);
			func(args);
			LeaveCriticalSection(&this->criticalSection);
		}

		void ThreadSafeEventRegistree::Register(ThreadSafeEventHandler* eventhandler, std::function<void(EventArgs&)> callback){
			if( deleting ) return;
			EnterCriticalSection(&this->criticalSection);
			if( this->eventhandler != NULL ){
				this->eventhandler->__Registree_Deattach(this);
			}
			eventhandler->__Registree_Attach(this, callback);
			this->eventhandler = eventhandler;
			deattaching = false;
			LeaveCriticalSection(&this->criticalSection);
		}

		void ThreadSafeEventRegistree::Unregister(){
			if( deleting ) return;
			deattaching = true;
			EnterCriticalSection(&this->criticalSection);
			if( eventhandler != NULL ){
				eventhandler->__Registree_Deattach(this);
				eventhandler = NULL;
			}
			LeaveCriticalSection(&this->criticalSection);
		}
		
		void ThreadSafeEventRegistree::__Registry_Deattach(){
			if( deleting ) return;
			deattaching = true;
			EnterCriticalSection(&this->criticalSection);
			/* Called from Registry */
			eventhandler = NULL;
			LeaveCriticalSection(&this->criticalSection);
		}
	}
}
