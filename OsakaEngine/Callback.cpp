 #include "stdafx.h"

#include "Registry.h"
#include "Registree.h"
#include "EventArgs.h"
#include "Callback.h"

namespace Osaka{
	namespace Component{
		
		Callback::Callback(){
			registree = NULL;
			id = 0;
		}
		Callback::~Callback(){
			if( id != 0 ){
				registree->__Registry_Deattach(id);
			}
			registree = NULL;
			id = 0;
			callback = nullptr;
		}

		void Callback::Call(EventArgs& e){
			if( id != 0 ){
				callback(e);
				if( e.auto_unregister ){
					__AutoRemove();
				}
			}
		}
		void Callback::__AutoRemove(){
			registree->__Registry_Deattach(id);
			/* Easier to just call itself */
			__Registree_Deattach(id);
		}
		/* Called from Registree (Register function) */
		void Callback::__Registree_Attach(Registree* r, std::function<void(EventArgs&)>& callback, const int id){
			if( this->id != 0 ){
				/* We only need to announce. */
				registree->__Registry_Deattach(id);
			}
			registree = r;
			this->callback = callback;
			this->id = id;
		}
		/* Called from Registree (or from this AutoRemove) */
		void Callback::__Registree_Deattach(const int id){
			if( registree == NULL ){
				return;
			}
			if( this->id != id ){
				throw std::exception("[Callback] ID mismatch");
			}
			callback = nullptr;
			registree = NULL;
			this->id = 0;
		}

		
	}
}
