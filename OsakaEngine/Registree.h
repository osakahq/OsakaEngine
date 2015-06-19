 #include "stdafx.h"

#ifndef COMPONENT_REGISTREE_H
#define COMPONENT_REGISTREE_H
#include "Utils.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace Component{
		class Registry;
		class EventArgs;

		class Registree
		{
		public:
			/* Gives away ownership */
			static Registree* CreateRawRegistree(){
				//If I need to override this function then, I should have like a global EventBuilder var.
				return new Registree();
			}

			Registree();
			~Registree();
			int Register(Registry* registry, std::function<void(EventArgs&)> callback, const int id = Utils::UniqueID());
			int Register(RegistryPTR registry, std::function<void(EventArgs&)> callback, const int id = Utils::UniqueID());
			/* Call this if you need to manually unhook */
			void Unregister(const int id);
			/* Called from Registry when Registry is being deleted. */
			void __Registry_Deattach(const int id);

		private:
			/* NOT Owner */
			std::unordered_map<int, Registry*> registries;
		};
	}
}
#endif