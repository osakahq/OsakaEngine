 #include "stdafx.h"
#include "ThreadSafeEventHandler.h"
#include "ThreadSafeEventRegistree.h"

namespace Osaka{
	namespace Component{
		
		ThreadSafeEventRegistree::ThreadSafeEventRegistree(){
			InitializeCriticalSection(&this->criticalSection);
			ref = NULL;
			deattaching = false;
		}
		ThreadSafeEventRegistree::~ThreadSafeEventRegistree(){
			Unhook();
			DeleteCriticalSection(&this->criticalSection);
		}
		void ThreadSafeEventRegistree::SetFunc(std::function<void(EventArgs&)> func){
			EnterCriticalSection(&this->criticalSection);
			this->func = func;
			LeaveCriticalSection(&this->criticalSection);
		}
		void ThreadSafeEventRegistree::CallFunc(EventArgs& args){
			EnterCriticalSection(&this->criticalSection);
			if( !deattaching ){ //var is volatile
				func(args);
			}
			LeaveCriticalSection(&this->criticalSection);
		}
		void ThreadSafeEventRegistree::Unhook(){
			deattaching = true;
			EnterCriticalSection(&this->criticalSection);
			//Only if you need to manually Unhook. (or ~destructor)
			if( ref != NULL ){
				ref->__Event_Unhook(this);
				ref = NULL;
			}
			LeaveCriticalSection(&this->criticalSection);
		}

		void ThreadSafeEventRegistree::__EventHandler_Attach(ThreadSafeEventHandler* ref, bool _throw){
			deattaching = false;
			EnterCriticalSection(&this->criticalSection);
			if( _throw && ref != NULL ){
				throw std::exception("[Event] ref must be NULL first.");
			}
			this->ref = ref;
			LeaveCriticalSection(&this->criticalSection);
		}
		void ThreadSafeEventRegistree::__EventHandler_Deattach(){
			deattaching = true; //just in case.
			EnterCriticalSection(&this->criticalSection);
			ref = NULL;
			LeaveCriticalSection(&this->criticalSection);
		}
	}
}
