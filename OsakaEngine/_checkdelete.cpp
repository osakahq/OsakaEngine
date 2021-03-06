#include "stdafx.h"
#include "ConsoleColors.h"
#include "Debug.h"
#include "_checkdelete.h"

bool _check_delete_init = false;
std::unordered_map<std::string, int> _check_delete_register;
//bool = multiple calls
std::unordered_map<std::string, bool> _check_delete_info;

void _STARTCHECKDELETE(bool ascension){
	std::cout << Osaka::Debug::yellow << "[+Debug] Start check. " << Osaka::Debug::white << std::endl;
	/* If it's false then only 1 call is expected to be called (one instance)
	 * If it's true then 2 calls are expected (multiple instances) */
	_check_delete_init = true;
	_check_delete_info["LoadingSceneScript"] = false;
		
	_check_delete_info["LoadingFadeScript"] = false;
	_check_delete_info["LoadingFadeCanvas"] = false;
	
	_check_delete_info["InitSceneArgs"] = false;
	
	_check_delete_info["LoadingArgs"] = true;
	_check_delete_info["LoadingFadeLayerArgs"] = true;
	
	if( ascension ){
		//_check_delete_info["AscApplication"] = false;
	}
}
	
void _CHECKDELETE(std::string classname, bool deconstructor){
	if( !_check_delete_init )
		return;
	//classname doesn't exist in _info map
	if( _check_delete_info.find(classname) == _check_delete_info.end() ){
		std::cout << Osaka::Debug::red << "[+Debug] Class " << classname << " is NOT registered in info." << Osaka::Debug::white << std::endl;
	}

	_check_delete_register[classname] += 1;
}
void _ENDCHECKDELETE(){
	for(auto it = _check_delete_info.begin(); it != _check_delete_info.end(); ++it){
		//the classname in info was not called at all
		if( _check_delete_register.find(it->first) == _check_delete_register.end() ){
			std::cout << Osaka::Debug::red << "[+Debug] Class " << it->first << " was not called at all." << Osaka::Debug::white << std::endl;
		}else{
			//if multipleclass is false then it shouldn't have been called more than once (one instance)
			if( _check_delete_info[it->first] == false && _check_delete_register[it->first] > 1 ){
				std::cout << Osaka::Debug::red << "[+Debug] Class " << it->first << " called more than once (check define)." << Osaka::Debug::white << std::endl;
			}else if( _check_delete_register[it->first] < 1 ){
				//If its true, it can be called many times (multiple instances)
				std::cout << Osaka::Debug::red << "[+Debug] Class " << it->first << " calls weren't completed (check define)." << Osaka::Debug::white << std::endl;
			}
		}
	}
	std::cout << Osaka::Debug::yellow << "[+Debug] End check. " << Osaka::Debug::white << std::endl;
}