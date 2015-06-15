 #include "stdafx.h"
#ifndef RPGLIB_RPGSCENE_H
#define RPGLIB_RPGSCENE_H
#include "EScene.h"
#include "osaka_forward.h"

#define RPGSCENE_MAX_LAYERS 20

namespace Osaka{
	namespace RPGLib{
		
		/* Some functions are completely overriden in OneLayerScene.h. So for modifications, please go over there as well. */
		class RPGScene : public Engine::EScene{
		public:
			RPGScene(std::string id, SceneScriptPTR& mainscript);
			virtual ~RPGScene();
			virtual void _delete() override;
			
			virtual void Start() override;

			/* Do not override this. Not used. */
			void Load() override;
			virtual void Load(RPGFactoryPTR& factory);
			virtual void Unload() override;

			virtual void Enter() override;
			virtual void ReadyStandBy(Engine::ESceneArgsPTR& params) override;
			virtual void ReadyShow(Engine::ESceneArgsPTR& params) override;
			virtual void Exit() override;

			virtual void StandBy() override;
			virtual void Focus() override;

			virtual void Update() override;
			virtual void Draw() override;

			virtual void End() override;

			//Functions for the layers
			void Stack(std::string id, LayerArgsPTR& args);
			void StackBefore(std::string id, std::string ref_layer, LayerArgsPTR& args);
			void StackAfter(std::string id, std::string ref_layer, LayerArgsPTR& args);
			void Switch(std::string id, LayerArgsPTR& args);

			void Remove(std::string id);
			void RemoveAll();
			void Add(LayerPTR layer);

			std::string GetId();
		/* ----------------------------------------------------------------------------------- */
		private:
			/* This is a helper var so that it can't add layers once the loop starts */
			bool started;
		protected:
			std::string  id;
			
			/* Owner of SceneScript */
			SceneScriptPTR mainscript;
			/* The cache version. */
			SceneScript* raw_mainscript;
			
			/* Owner (layers). ID of the layer. 
			 * It is responsability of the factory to add the layers into the vector */
			std::unordered_map<std::string, LayerPTR> layers;
			/* This is the one we use to search the layers. */
			std::unordered_map<std::string, Layer*> raw_layers;
			/* Because map iterator is too slow, we need either vector[] or array. Array because we don't remove or add constantly at all.
			 * This array holds ALL the layers too. This array is used to call ALL the layers. For example, End(), Enter(). */
			Layer* array_raw_layers[RPGSCENE_MAX_LAYERS];
			/* Holds the size of raw_layers which is identical of layers but with raw pointers */
			int map_size;

			/* Layers are owned in the unorderedmap */
			std::vector<Layer*> stack_layers;
			/* Helper copy var. This is used to loop through stack_layers. (RemoveAll for example) */
			Layer* copy_stack_layers[RPGSCENE_MAX_LAYERS];

			/* This is a temp stack, so when the loop Update is running, it doesn't mess with it. */
			Layer* temp_stack_layers[RPGSCENE_MAX_LAYERS];
			int temp_stack_layers_items;

			bool stackHasChanged;
			
			bool focus;
			bool standby;
			bool instack;
			bool hidden; //This can only be set with `StandByHide()` by the scene itself

			/* This is a method if the scene wants to not render or update while there is another scene stacked on
			 * This is private because the only way the scene know it is not showing, its itself.
			 *	. Remember that each script knows what the other script does. Like I have been saying, in script code almost anything is valid 
			 * This may only be called after calling `Stack("newscene"); this->StandByHide();` 
			 * Just remember that EApplication will call `StandBy()` regardless. */
			void StandByHide(bool val);

		};
	}
}
#endif