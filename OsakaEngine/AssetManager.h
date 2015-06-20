 #include "stdafx.h"
#ifndef RPGLIB_ASSETMANAGER_H
#define RPGLIB_ASSETMANAGER_H
#include "osaka_forward.h"

namespace Osaka{
	namespace Component{
		class EventArgs;
	}
	namespace RPGLib{
		/* This is used for the loading thread to "consume" (So I can pass params to the thread)
		 * See the thread function (ProcessLoad()) */
		struct LoadThreadParams{
			LoadThreadParams(){
				scene = NULL;
				callback = nullptr;
			}
			~LoadThreadParams(){
				scene = NULL;
				callback = nullptr;
			}
			/* NOT Owner. Owner is in `unordered_map_scene_data` which is in GameData */
			scene_data* scene;
			std::function<void()> callback;
		};
		/* Do not be confused with GameDataLoader. This is for scene.load/unload and asset loading 
		 * TODO: For now, unload is not yet implemented (only videos are unload-able) */
		class AssetManager {
		public:
			AssetManager(Debug::Debug* debug, unorderedmap_assets_type& assets_type, unorderedmap_asset_initload_data& assets_initload, unorderedmap_scene_data& scenes);
			~AssetManager();
			
			void Init(RPGApplication* app);
			void ProcessLoad();
			void LoadScene(const std::string& scene, std::function<void()> callback);
			/* The loop ended and needs to unload the loaded scenes. */
			void End();
			/* NOT Owner. Owner is in RPGApplication */
			TextureManager* texturem;
			/* NOT Owner. Owner is in RPGApplication */
			FontManager* fontm;
			/* NOT Owner. Owner is in RPGApplication */
			SoundManager* soundm;
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner */
			RPGApplication* app;
			/* Owner. This thread is used to do the asset loading/class load/unload */
			HANDLE loadThread;
			/* Owner. This is a event/lock to signal the load thread that there is a new scene to "consume" */
			HANDLE sceneToLoadEvent;
			/* Owner. This variable is accessed by 2 threads. See declaration explanation */
			LoadThreadParams threadParams;
			/* This variable is to let the loadThread:Function to exit gracefully */
			volatile bool signalStopLoadThread;

			/* NOT Owner. The map to know which asset is what type */
			const unorderedmap_assets_type* assets_type;
			/* NOT Owner. The struct info from the XML */
			const unorderedmap_asset_initload_data* assets_initload;
			/* NOT Owner. The struct info from the XML */
			const unorderedmap_scene_data* scenes;

			/* Helper function: Loads the asset depending on the type */
			void LoadAsset(const std::string& id);

			/* NOT Owner */
			Debug::Debug* debug;

			//Variables used for the loading process...
			std::unordered_map<std::string, bool> loadedScenes;
			std::unordered_map<std::string, bool> loadedAssets;
			/* This can be called in both threads (main/loading thread) */
			void SceneIsLoaded();
			void ProcessScene(const scene_data& data, bool firstlevel);
			void ProcessRelatedScenes(const std::unordered_map<std::string, related_scene_data>& related_scenes_data, bool firstlevel);
		};
	}
}
#endif