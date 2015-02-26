 #include "stdafx.h"

#ifndef NETWORK_RECIEVEEVENTARGS_H
#define NETWORK_RECIEVEEVENTARGS_H
#include "EventArgs.h"

namespace Osaka{
	namespace Network{

		class RecieveEventArgs : public Component::EventArgs
		{
	
		public:
			RecieveEventArgs();
			
			RecieveEventArgs(std::vector<std::string>* messages);
			bool find(const char* str);

			/* NOT Owner. And this pointer is invalid when `Raise()` call ends. */
			std::vector<std::string>* messages;
		};
	}
}
#endif
