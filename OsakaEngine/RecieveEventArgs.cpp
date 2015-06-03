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
	}
}
