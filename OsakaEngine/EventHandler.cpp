 #include "stdafx.h"
#include "ConsoleColors.h"
#include "EventArgs.h"
#include "Registree.h"
#include "EventHandler.h"

namespace Osaka{
	namespace Component{
		
		EventHandler::EventHandler(){
			
		}
		EventHandler::~EventHandler(){
			for(auto it = registrees.begin(); it != registrees.end(); ++it){
				it->second->r->__Registry_Deattach(it->first);
				delete it->second;
			}
		}

		void EventHandler::Raise(EventArgs& e){
			for(auto it = registrees.begin(); it != registrees.end(); ++it){
				it->second->callback(e);
				if( e.auto_unregister ){
					remove_queue.push_back(it->first);
				}
				//We need to reset the vars because, if we don't it's gonna look like every Registree wants to auto unregister
				e.Reset();
			}
			if( !remove_queue.empty() ){
				__AutoRemove();
			}
		}
		void EventHandler::__AutoRemove(){
			for(unsigned int i = 0; i < remove_queue.size(); ++i){
				registrees[remove_queue[i]]->r->__Registry_Deattach(remove_queue[i]);
				registrees.erase(remove_queue[i]);
			}
			remove_queue.clear();
		}
		void EventHandler::__Registree_Attach(Registree* r, std::function<void(EventArgs&)>& callback, const int id){
			auto it = registrees.find(id);
			if( it != registrees.end() ){
				it->second->r->__Registry_Deattach(id);
				registrees.erase(it);
			}
			registrees[id] = new __eventhandler_info(r, callback);
		}
		void EventHandler::__Registree_Deattach(const int id){
			//Called from Registree
			/* The reason we don't need to check anything is because this is different than attach.
			 * If were are replacing an id, we must make sure to announce to deattach it. */
			registrees.erase(id);
		}
	}
}