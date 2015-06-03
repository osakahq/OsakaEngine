 #include "stdafx.h"
#ifndef RPGLIB_RPGSCENE_H
#define RPGLIB_RPGSCENE_H
#include "EScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		/* Some functions are completely overriden in OneLayerScene.h. So for modifications, please go over there as well. */
		class RPGScene : public Engine::EScene{
		public:
			RPGScene(std::string id, SceneScriptPTR& mainscript);
			virtual ~RPGScene();
			virtual void _delete();
			
			virtual void Load();
			virtual void Unload();

			virtual void ReadyStandBy(Engine::ESceneArgsPTR& params);
			virtual void ReadyShow(Engine::ESceneArgsPTR& params);
			virtual void Exit();

			virtual void StandBy();
			virtual void Focus();

			virtual void Update();
			virtual void Draw();

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
		protected:
			std::string  id;
			
			/* Owner of SceneScript */
			SceneScriptPTR mainscript;

			/* Owner (layers). ID of the layer. 
			 * It is responsability of the factory to add the layers into the vector */
			std::unordered_map<std::string, LayerPTR> layers;
			/* Layers are owned in the unorderedmap */
			std::vector<LayerPTR> stack_layers;
			/* This is a temp stack, so when the loop Update is running, it doesn't mess with it. */
			std::vector<LayerPTR> temp_stack_layers;
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