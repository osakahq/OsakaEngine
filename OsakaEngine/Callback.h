 #include "stdafx.h"

#ifndef COMPONENT_CALLBACK_H
#define COMPONENT_CALLBACK_H
#include "Registry.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace Component{
		
		class Callback : public Registry{
		public:
			Callback();
			~Callback();

			void Call(EventArgs& e);
			/* Called from Registree (Register function) */
			void __Registree_Attach(Registree* r, std::function<void(EventArgs&)>& callback, const int id);
			/* Called from Registree (or from this AutoRemove) */
			void __Registree_Deattach(const int id);

		private:
			Registree* registree;
			std::function<void(EventArgs&)> callback;
			int id;

			void __AutoRemove();
		};
	}
}
#endif