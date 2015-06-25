 #include "stdafx.h"

#include "LayerArgs.h"
#include "ESceneArgs.h"
#include "DrawableModifierArgs.h"

const bool* __GLOBALVARS__debug = NULL;

namespace Osaka{
	namespace Engine{
		std::shared_ptr<ESceneArgs> EmptyESceneArgsPTR = std::make_shared<ESceneArgs>();
		ESceneArgs EmptyESceneArgs;
	}
	namespace RPGLib{
		LayerArgs EmptyLayerArgs;
		DrawableModifierArgs EmptyDrawableModifierArgs;
	}
}
