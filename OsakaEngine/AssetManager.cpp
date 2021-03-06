 #include "stdafx.h"

#include "RPGApplication.h"
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
		AssetManager::AssetManager(Debug::Debug* debug, unorderedmap_assets_type& assets_type, unorderedmap_asset_initload_data& assets_initload, unorderedmap_scene_data& scenes){
			loadThread = NULL;
			sceneToLoadEvent = NULL;
			signalStopLoadThread = false;

			this->assets_type = &assets_type;
			this->assets_initload = &assets_initload;
			this->scenes = &scenes;

			this->debug = debug;

			texturem = NULL;
			fontm = NULL;
			soundm = NULL;
			app = NULL;
		}
		AssetManager::~AssetManager(){
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
			texturem = NULL;
			fontm = NULL;
			soundm = NULL;
			debug = NULL;

			/* If we don't do this, the copied variables will never be freed */
			threadParams.callback = nullptr;
			threadParams.scene = NULL;
			app = NULL;
			
			//We have the const pointer so.. don't do this:
			//assets_type.clear();
			//assets_initload.clear();
			//scenes.clear();
			assets_type = NULL;
			assets_initload = NULL;
			scenes = NULL;

			loadedScenes.clear();
			loadedAssets.clear();
		}
		
		void AssetManager::Init(RPGApplication* app){
			LOG("[AssetManager] Init\n");
			this->app = app;
			for( auto it = assets_initload->begin(); it != assets_initload->end(); ++it ){
				LoadAsset((*it->second).id);
			}
			//Initial state = false
			sceneToLoadEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("AssetManager_NewScene"));
			loadThread = CreateThread(NULL, 0, &AssetManager_ProcessLoad, this, 0, NULL);
		}

		void AssetManager::LoadScene(const std::string& scene, std::function<void()> callback){
			/* If signaled to stop or if the event hasn't resetted yet */
			if( signalStopLoadThread || (DWORD)WaitForSingleObject(sceneToLoadEvent, 0) == WAIT_OBJECT_0 ){
				debug->e("[AssetManager] Can't load another scene when a scene is already being loaded.");
				return;
			}

			auto it_scene = scenes->find(scene);
			if( it_scene == scenes->end() ){
				debug->e("[AssetManager] Scene does not exists: " + scene);
			}

			/* std::function need to be set to `nullptr` when done */
			threadParams.callback = callback;
			threadParams.scene = it_scene->second;

			SetEvent(sceneToLoadEvent);
		}

		void AssetManager::SceneIsLoaded(){
			//WARNING: the callback is using rawpointer (see RPGLoadingScene::SceneTransition())
			threadParams.callback();
			/* If we don't do this, the copied variables will never be freed */
			threadParams.callback = nullptr;
			threadParams.scene = NULL;
		}

		void AssetManager::ProcessLoad(){
			while(!signalStopLoadThread){
				WaitForSingleObject(sceneToLoadEvent, INFINITE);
				if( signalStopLoadThread )
					break;

				ProcessScene(*threadParams.scene, true);
				ResetEvent(sceneToLoadEvent);
				SceneIsLoaded();
			}
			LOG("[AssetManager] ProcessLoad thread ended gracefully.\n");
		}

		void AssetManager::End(){
			for(auto it = loadedScenes.begin(); it != loadedScenes.end(); ++it){
				if( it->second ){ //value is boolean
					app->CallUnload(it->first);
					it->second = false;
				}
			}
		}

		/* Helper function */
		void AssetManager::LoadAsset(const std::string& id){
			if( loadedAssets.find(id) != loadedAssets.end() ){
				//Asset is already loaded.
				return;
			}
			auto it = assets_type->find(id);
			if( it == assets_type->end() ){
				debug->e("[AssetManager] Asset was not defined. (asset_types:id="+id+")");
			}

			AssetType::Value type = (AssetType::Value)it->second;
			switch(type){
			case AssetType::SOUND:
				soundm->LoadSound(id);
				break;
			case AssetType::TEXTURE:
				texturem->LoadTexture(id);
				break;
			case AssetType::VIDEO:
				debug->e("[AssetManager] Asset video is not yet implemented");
				break;
			default:
				debug->e("[AssetManager] Asset \"type\" was not defined. (asset_types:id="+id+")");
				break;
			}
			loadedAssets[id] = true;
		}

		/* I'm just processing the data. */
		void AssetManager::ProcessScene(const scene_data& data, bool firstlevel){
			if( loadedScenes.find(data.id) == loadedScenes.end() ){
				//If the scene is not loaded...
				for( auto it = data.assets.begin(); it != data.assets.end(); ++it ){
					LoadAsset(it->second.id);
				}
				app->CallLoad(data.id);
				loadedScenes[data.id] = true;
#ifdef _DEBUG
				LOG("[AssetManager] Loading scene: %s\n", data.id.c_str());
#endif
			}
			
			ProcessRelatedScenes(data.related_scenes_data, firstlevel);
		}

		/* I'm just processing the list. It's fine to use raw pointer (raw_pointer)
		 * ! If `firstlevel` is true it means that these related scenes are from the primary scene to be loaded
		 *		. Because a scene that is not linked and is not the primary scene to be loaded, there is no more recursion*/
		void AssetManager::ProcessRelatedScenes(const std::unordered_map<std::string, related_scene_data>& related_scenes_data, bool firstlevel){
			for( auto it = related_scenes_data.begin(); it != related_scenes_data.end(); ++it ){
				if( it->second.linked ){
					//Scenes are always loaded when linked (remember, there is no unload atm)
					ProcessScene(*scenes->at(it->second.id), false); //firstlevel is no longer.
				}else if( firstlevel && it->second.always_load ){
					//only load through always-load if its firstlevel (main scene to load)
					ProcessScene(*scenes->at(it->second.id), false);
				}
			}
		}
	}
}