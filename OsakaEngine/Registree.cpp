 #include "stdafx.h"

#include "Utils.h"
#include "EventArgs.h"
#include "Registry.h"
#include "Registree.h"

namespace Osaka{
	namespace Component{
		
		Registree::Registree(){
				
		}
		Registree::~Registree(){
			for(auto it = registries.begin(); it != registries.end(); ++it){
				it->second->__Registree_Deattach(it->first);
			}
		}

		int Registree::Register(RegistryPTR registry, std::function<void(EventArgs&)> callback, const int id){
			//It doesnt matter if it's PTR or raw pointer. When it goes away, it goes away.
			return Register(registry.get(), callback, id);
		}
		int Registree::Register(Registry* registry, std::function<void(EventArgs&)> callback, const int id){
			auto it = registries.find(id);
			if( it != registries.end() ){
				/* Has to have the same code as Unregister */
				it->second->__Registree_Deattach(id);
				registries.erase(it);
			}
			registry->__Registree_Attach(this, callback, id);
			registries[id] = registry;
			return id;
		}

		/* Call this if you need to manually unhook */
		void Registree::Unregister(const int id){
			auto it = registries.find(id);
			if( it != registries.end() ){
				/* This code is copied in Register */
				it->second->__Registree_Deattach(id);
				registries.erase(it);
			}
		}

		/* Called from Registry when Registry is being deleted. */
		void Registree::__Registry_Deattach(const int id){
			registries.erase(id);
		}

	}
}
