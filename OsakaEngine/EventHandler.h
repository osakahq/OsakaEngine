 #include "stdafx.h"

#ifndef COMPONENT_EVENTHANDLER_H
#define COMPONENT_EVENTHANDLER_H

#include "Registry.h"
namespace Osaka{
	namespace Component{
		class EventArgs;
		class Registree;
		
		struct __eventhandler_info{
			__eventhandler_info(Registree* _r, std::function<void(EventArgs&)> _callback) : r(_r), callback(_callback){}
			~__eventhandler_info(){}
			/* NOT Owner */
			Registree* r;
			std::function<void(EventArgs&)> callback;
		};

		class EventHandler : public Registry
		{
		private:
			/* Owner */
			std::unordered_map<int, __eventhandler_info*> registrees;
			/* int = id. This is a temp list so that in raise you can auto unregister */
			std::vector<int> remove_queue;

			/* Child class must implement this so that you can auto unregister */
			void __AutoRemove() override;
		public:
			EventHandler();
			~EventHandler();
			void Raise(EventArgs& e);

			/* Called from Registree */
			void __Registree_Attach(Registree* r, std::function<void(EventArgs&)>& callback, const int id) override;
			/* Called from Registree when Registree is being deleted. or manually */
			void __Registree_Deattach(const int id) override;
		};
	}
}
#endif