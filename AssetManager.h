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
			std::string scene;
			std::function<void(Component::EventArgs&)> callback;
		};
		/* Do not be confused with GameDataLoader. This is for scene.load/unload and asset loading 
		 * TODO: For now, unload is not yet implemented (only videos are unload-able) */
		class AssetManager {
		public:
			AssetManager(Debug::DebugPTR& debug, unorderedmap_assets_typePTR& assets_type, unorderedmap_asset_initload_dataPTR& assets_initload, unorderedmap_scene_dataPTR& scenes);
			~AssetManager();
			void _delete();
			
			void Init();
			void ProcessLoad();
			void LoadScene(std::string scene, std::function<void(Component::EventArgs&)> callback);
			

			/* Owner. Managers */
			TextureManagerPTR texturem;
			FontManagerPTR fontm;
			SoundManagerPTR soundm;
		/* ----------------------------------------------------------------------------------- */
		private:
			/* Owner. This thread is used to do the asset loading/class load/unload */
			HANDLE loadThread;
			/* Owner. This is a event/lock to signal the load thread that there is a new scene to "consume" */
			HANDLE sceneToLoadEvent;
			/* Owner. This variable is accessed by 2 threads. See declaration explanation */
			LoadThreadParams threadParams;
			/* This variable is to let the loadThread:Function to exit gracefully */
			volatile bool signalStopLoadThread;

			/* NOT Owner. The map to know which asset is what type */
			unorderedmap_assets_typePTR assets_type;
			/* NOT Owner. The struct info from the XML */
			unorderedmap_asset_initload_dataPTR assets_initload;
			/* NOT Owner. The struct info from the XML */
			unorderedmap_scene_dataPTR scenes;

			/* Helper function: Loads the asset depending on the type */
			void LoadAsset(const std::string id);

			/* NOT Owner */
			Debug::DebugPTR debug;
		};
	}
}
#endif