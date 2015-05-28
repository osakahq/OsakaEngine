 #include "stdafx.h"
#ifndef RPGLIB_RPGSCENE_H
#define RPGLIB_RPGSCENE_H
#include "EScene.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class RPGScene : public Engine::EScene{
		public:
			RPGScene(std::string id, RPGApplicationPTR& app);
			virtual ~RPGScene();
			virtual void _delete();
			
			virtual void Load();
			virtual void Unload();

			virtual void ReadyStandBy(Engine::ESceneArgsPTR& params);
			virtual void ReadyShow(Engine::ESceneArgsPTR& params);
			virtual void Exit();

			virtual void StandBy();
			virtual void Focus();

			void Update();
			void Draw();

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
			
			/* Owner (layers). ID of the layer. 
			 * It is responsability of the derived class to add the layers into the vector */
			std::unordered_map<std::string, LayerPTR> layers;
			/* Layers are owned in the unorderedmap */
			std::vector<LayerPTR> stack_layers;

			/* NOT Owner */
			RPGApplicationPTR app;

			bool focus;
			bool standby;
			bool instack;
			bool hidden; //This can only be set with `StandByHide()` by the scene itself

			/* This is a method if the scene wants to not render or update while there is another scene stacked on
			 * This is private because the only way the scene know it is not showing, its itself.
			 *	. Remember that each script knows what the other script does. Like I have been saying, in script code almost anything is valid 
			 * This may only be called after calling `Stack("newscene"); this->StandByHide();` 
			 * Just remember that EApplication will call `StandBy()` regardless. */
			void StandByHide();

			/* This is where the script code goes. */
			virtual void ReadyEx(Engine::ESceneArgsPTR& params);
			/* The reason there is a special `UpdateEx()` is to not worry about copying the code inside `Update()` */
			virtual void UpdateEx();
		};
	}
}
#endif