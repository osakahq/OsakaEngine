 #include "stdafx.h"
#include "EventArgs.h"
#include "Debug.h"
#include "gamedata_include.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "AssetManager.h"
namespace Osaka{
	namespace RPGLib{
		
		static DWORD WINAPI AssetManager_ProcessLoad(LPVOID ptr){
			static_cast<AssetManager*>(ptr)->ProcessLoad();
			return 0;
		}
		AssetManager::AssetManager(Debug::DebugPTR& debug, unorderedmap_assets_typePTR& assets_type, unorderedmap_asset_initload_dataPTR& assets_initload, unorderedmap_scene_dataPTR& scenes){
			loadThread = NULL;
			sceneToLoadEvent = NULL;
			signalStopLoadThread = false;

			this->assets_type = assets_type;
			this->assets_initload = assets_initload;
			this->scenes = scenes;

			this->debug = debug;
		}
		AssetManager::~AssetManager(){
#ifdef _DEBUG
			_CHECKDELETE("AssetManager");
#endif	
			signalStopLoadThread = true;
			/* We need to make sure to signal the event or it will be forever waiting */
			SetEvent(sceneToLoadEvent);
			if( loadThread != NULL ){
				WaitForSingleObject(loadThread, 200);
				CloseHandle(loadThread);
				loadThread = NULL;
			}
			if( sceneToLoadEvent != NULL ){
				CloseHandle(sceneToLoadEvent);
				sceneToLoadEvent = NULL;
			}
		}
		void AssetManager::_delete(){
			signalStopLoadThread = true;
			SetEvent(sceneToLoadEvent);

			texturem->_delete(); texturem = nullptr;
			fontm->_delete(); fontm = nullptr;
			soundm->_delete(); soundm = nullptr;

			assets_type = nullptr;
			assets_initload = nullptr;
			scenes = nullptr;

			debug = nullptr;
		}

		void AssetManager::Init(){
			debug->l("[AssetManager] Init");
			for( auto it = assets_initload->begin(); it != assets_initload->end(); ++it ){
				LoadAsset((*it->second).id);
			}
			//Initial state = false
			sceneToLoadEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("AssetManager_NewScene"));
			loadThread = CreateThread(NULL, 0, &AssetManager_ProcessLoad, this, 0, NULL);
		}

		void AssetManager::LoadScene(std::string scene, std::function<void()> callback){
			/* If signaled to stop or if the event hasn't resetted yet */
			if( signalStopLoadThread || (DWORD)WaitForSingleObject(sceneToLoadEvent, 0) == WAIT_OBJECT_0 ){
				debug->e("[AssetManager] Can't load another scene when a scene is already being loaded.");
				return;
			}
			threadParams.callback = callback;
			threadParams.scene = scene;
			SetEvent(sceneToLoadEvent);
		}

		void AssetManager::ProcessLoad(){
			while(!signalStopLoadThread){
				WaitForSingleObject(sceneToLoadEvent, INFINITE);
				if( signalStopLoadThread )
					break;

				debug->l("TODO PROCESSLOAD");
				//WARNING: the callback is using rawpointer (see RPGLoadingScene::SceneTransition())
				threadParams.callback();
				ResetEvent(sceneToLoadEvent);
			}
			debug->l("[AssetManager] ProcessLoad thread ended gracefully.");
		}

		/* Helper function */
		void AssetManager::LoadAsset(const std::string id){
			if( assets_type->find(id) == assets_type->end() ){
				debug->e("[AssetManager] Asset was not defined. (asset_types:id="+id+")");
			}

			AssetType::Value type = (AssetType::Value)assets_type->at(id);
			switch(type){
			case AssetType::SOUND:
				soundm->LoadSound(id);
				break;
			case AssetType::TEXTURE:
				texturem->LoadTexture(id);
				break;
			case AssetType::VIDEO:
				debug->l("[AssetManager] Asset video is not yet implemented");
				break;
			default:
				debug->e("[AssetManager] Asset \"type\" was not defined. (asset_types:id="+id+")");
				break;
			}
		}
	}
}