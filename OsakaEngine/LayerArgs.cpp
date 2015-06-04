 #include "stdafx.h"
#include "LayerArgs.h"
namespace Osaka{
	namespace RPGLib{
		LayerArgs::LayerArgs(){

		}
		LayerArgs::~LayerArgs(){

		}
		//Global empty layer params
		std::shared_ptr<LayerArgs> EmptyLayerArgsPTR = std::make_shared<LayerArgs>();
	}
}