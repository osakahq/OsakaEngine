 #include "stdafx.h"

#ifndef NETWORK_RECIEVEEVENTARGS_H
#define NETWORK_RECIEVEEVENTARGS_H
#include "EventArgs.h"

namespace Osaka{
	namespace Network{

		class RecieveEventArgs : public Component::EventArgs
		{
	
		public:
			//char message[DEFAULT_BUFLEN];

			std::vector<std::string>* messages;

			RecieveEventArgs();
			//RecieveEventArgs(char* message);
			RecieveEventArgs(std::vector<std::string>* messages);
			bool find(const char* str);
			//char* message and char message[] are the same things
			//void setMessage(char* message);
		};
	}
}
#endif
