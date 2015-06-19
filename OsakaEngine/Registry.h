 #include "stdafx.h"

#ifndef COMPONENT_REGISTRY_H
#define COMPONENT_REGISTRY_H

namespace Osaka{
	namespace Component{
		class EventArgs;
		class Registree;

		class Registry{
		private:
			virtual void __AutoRemove() = 0;
		public:
			virtual void __Registree_Attach(Registree* r, std::function<void(EventArgs&)>& callback, const int id) = 0;
			virtual void __Registree_Deattach(const int id) = 0;
		private:
		};
	}
}
#endif