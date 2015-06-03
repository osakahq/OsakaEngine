 #include "stdafx.h"
#ifndef RPGLIB_LAYERARGS_H
#define RPGLIB_LAYERARGS_H

namespace Osaka{
	namespace RPGLib{

		class LayerArgs{
		public:
			LayerArgs();
			virtual ~LayerArgs();
		private:
			
		};

		extern std::shared_ptr<LayerArgs> EmptyLayerArgsPTR;

	}
}
#endif