 #include "stdafx.h"
#include "Debug.h"
#include "Utils.h"
#include "physfsrwops.h"
#include "PhysicsFSFileLoader.h"
#include "osaka_forward.h"

namespace Osaka{
	namespace Engine{
		PhysicsFSFileLoader::PhysicsFSFileLoader(Debug::DebugPTR& debug, const char* filename){
			this->debug = debug;

			PHYSFS_init(NULL);
			AddFile(filename);
		}
		PhysicsFSFileLoader::~PhysicsFSFileLoader(){
			PHYSFS_deinit();
		}
		void PhysicsFSFileLoader::_delete(){
			debug = nullptr;
		}
		void PhysicsFSFileLoader::AddFile(const char* filename){
			if( !Utils::FileExists(filename) )
				debug->e("[PhysicsFSFileLoader] Package does not exists:"+std::string(filename));
			PHYSFS_addToSearchPath(filename, 1);
		}

		//Parameter 1 = automatically frees up the RW resource
		Mix_Music* PhysicsFSFileLoader::LoadMusic(const char* path){
			std::string temp = path;
			std::replace(temp.begin(), temp.end(), '\\', '/');
			if( !PHYSFS_exists(temp.c_str()) )
				debug->e("[PhysicsFSFileLoader] File does not exists: " + temp);

			SDL_RWops* rw = PHYSFSRWOPS_openRead(temp.c_str());
			return Mix_LoadMUS_RW(rw, 1);
		}
		Mix_Chunk* PhysicsFSFileLoader::LoadWAV(const char* path){
			std::string temp = path;
			std::replace(temp.begin(), temp.end(), '\\', '/');
			if( !PHYSFS_exists(temp.c_str()) )
				debug->e("[PhysicsFSFileLoader] File does not exists: " + temp);

			SDL_RWops* rw = PHYSFSRWOPS_openRead(temp.c_str());
			return Mix_LoadWAV_RW(rw, 1);
		}
		SDL_Surface* PhysicsFSFileLoader::LoadImageSurface(const char* path){
			std::string temp = path;
			std::replace(temp.begin(), temp.end(), '\\', '/');
			if( !PHYSFS_exists(temp.c_str()) )
				debug->e("[PhysicsFSFileLoader] File does not exists: " + temp);

			SDL_RWops* rw = PHYSFSRWOPS_openRead(temp.c_str());
			return IMG_Load_RW(rw, 1);
		}
		/*PHYSFS_init(NULL);
		PHYSFS_addToSearchPath("tests\\test_physfs.7z", 1);
		if( PHYSFS_exists("cinematics.png") ){
			printf("freaking awesome\n");
			SDL_RWops* rw;
			if( (rw = PHYSFSRWOPS_openRead("cinematics.png")) == NULL){
				printf("rw is null\n");
			}else{
				SDL_Surface* loadedSurface = IMG_Load_RW(rw, 1);
				if( loadedSurface == NULL ){
					printf("surface is null\n");
				}else{
					printf("surface is load and ready\n");
					printf("surface w:%d\n", loadedSurface->w);
					printf("surface h:%d\n", loadedSurface->h);
					SDL_FreeSurface(loadedSurface);
				}
			
				// Just in case?
				SDL_FreeRW(rw);
			}
		
		}else{
			printf("fuck you");
		}
		PHYSFS_deinit();*/
	}
}