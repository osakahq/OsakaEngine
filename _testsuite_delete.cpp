#include "stdafx.h"
#include "ConsoleColors.h"
#include "Debug.h"
#include "_testsuite_delete.h"

#ifdef _DEBUG
//2 means _delete and ~class calls are expected
//1 means only ~class call is expected
#define _CHECK_DELETE_NORMAL_CALLS 1
	bool _check_delete_init = false;
	std::unordered_map<std::string, int> _check_delete_register;
	//bool = multiple calls
	std::unordered_map<std::string, bool> _check_delete_info;

	void _STARTCHECKDELETE(){
		std::cout << Osaka::Debug::yellow << "[+Debug] Start check. " << Osaka::Debug::white << std::endl;
		_check_delete_init = true;
		_check_delete_info["Debug"] = false;
		_check_delete_info["Log"] = false;
		_check_delete_info["DefaultFileLoader"] = false;
		_check_delete_info["EApplication"] = false;
		_check_delete_info["SDLLib"] = false;
		_check_delete_info["ServerConn"] = false;
		_check_delete_info["RPGApplication"] = false;
		_check_delete_info["TextureManager"] = false;
		_check_delete_info["Factory"] = false;
		_check_delete_info["GameDataLoader"] = false;
		_check_delete_info["GameData"] = false;
		_check_delete_info["GameData_delete"] = false;
		_check_delete_info["RPGLoadingScene"] = false;
		_check_delete_info["RPGLoadingScene_delete"] = false;
		_check_delete_info["LoadingUI"] = false;
		_check_delete_info["LoadingScript"] = false;
		_check_delete_info["LoadingCanvas"] = false;
		_check_delete_info["GameSessionManager"] = false;
		_check_delete_info["AssetManager"] = false;
		_check_delete_info["TimeManager"] = false;

		_check_delete_info["RPGScene_delete"] = true;
		_check_delete_info["Canvas_delete"] = true;
		_check_delete_info["Script_delete"] = true;
		_check_delete_info["UserInterface_delete"] = true;
		
		_check_delete_info["EScenePassParams"] = true;
		_check_delete_info["LoadingPassParams"] = true;

		_check_delete_info["RPGScene"] = true;
		_check_delete_info["Texture"] = true;
		_check_delete_info["Sound"] = true;
		_check_delete_info["Music"] = true;
		_check_delete_info["SoundEffect"] = true;
		_check_delete_info["UserInterface"] = true;
		_check_delete_info["Script"] = true;
		_check_delete_info["Canvas"] = true;
		_check_delete_info["GameSession"] = true;
		_check_delete_info["Timer"] = true;
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
				//if multipleclass is false and if calls more than 2 (2 because of _delete and ~class)
				if( _check_delete_info[it->first] == false && _check_delete_register[it->first] > _CHECK_DELETE_NORMAL_CALLS ){
					std::cout << Osaka::Debug::red << "[+Debug] Class " << it->first << " called more than once (_delete -or- ~class [check define])." << Osaka::Debug::white << std::endl;
				}else if( _check_delete_register[it->first] < _CHECK_DELETE_NORMAL_CALLS ){
					std::cout << Osaka::Debug::red << "[+Debug] Class " << it->first << " calls weren't completed." << Osaka::Debug::white << std::endl;
				}
			}
		}
		std::cout << Osaka::Debug::yellow << "[+Debug] End check. " << Osaka::Debug::white << std::endl;
	}
#endif