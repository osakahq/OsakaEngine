 #include "stdafx.h"
#include "EventArgs.h"
#include "RecieveEventArgs.h"

namespace Osaka{
	namespace Network{

		RecieveEventArgs::RecieveEventArgs() : Component::EventArgs() {
	
		}
		RecieveEventArgs::RecieveEventArgs(std::vector<std::string>* messages){
			Component::EventArgs();
			this->messages = messages;
		}

		bool RecieveEventArgs::find(const char* str){
			for(std::size_t i = 0; i != this->messages->size(); i++) {
				if( strcmp(this->messages->at(i).c_str(), str) == 0 ){
					return true;
				}
			}
			return false;
		}
		//RecieveEventArgs::RecieveEventArgs(char* message){
			//EventArgs();
			//this->setMessage(message);
		//}
		//void RecieveEventArgs::setMessage(char* message){
			//char* message and char message[] are the same things
			//Doesn't matter if the pointer (message) goes away because I copy the value
			//strcpy_s(this->message, message);
		//}

	}
}
