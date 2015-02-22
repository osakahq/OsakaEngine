// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once
#define WIN32_LEAN_AND_MEAN

#include "targetver.h"

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include <stdio.h>
#include <tchar.h>
#include <cstdlib>
#include <string>
#include <memory>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>

#include <unordered_map>
#include <stack>
#include <functional>
#include <iostream>
#include <fstream>

#include <algorithm> 
#include <cctype>
#include <locale>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <physfs.h>

// Memory leak detection
#ifdef _CRTDBG_MAP_ALLOC
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif
//-----------------------------------
#ifdef _DEBUG
	#include "_testsuite_delete.h"
#endif

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
