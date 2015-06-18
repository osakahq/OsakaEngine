 
#ifndef RPGLIB_GLOBALVARS_H
#define RPGLIB_GLOBALVARS_H

namespace Osaka{
	namespace Engine{
		class ESceneArgs;
		extern std::shared_ptr<ESceneArgs> EmptyESceneArgsPTR;
		extern ESceneArgs EmptyESceneArgs;
	}
	namespace RPGLib{
		class LayerArgs;
		extern LayerArgs EmptyLayerArgs;
	}
}
#endif
