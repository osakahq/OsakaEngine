 
#ifndef RPGLIB_GLOBALVARS_H
#define RPGLIB_GLOBALVARS_H

extern const bool* __GLOBALVARS__debug;
/* Before calling LOG, we gotta make sure it is initialized. This is initialized in Debug.cpp */
#define LOG(...) if( *__GLOBALVARS__debug ){ printf(__VA_ARGS__); }

#define MULTIPLE_LOG_START(...) if( *__GLOBALVARS__debug ){ printf(__VA_ARGS__);
#define MULTIPLE_LOG(...) printf(__VA_ARGS__);
#define MULTIPLE_LOG_END(...) printf(__VA_ARGS__); }

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
