 #include "stdafx.h"

#ifndef RPGLIB_FPSCOUNTER_H
#define RPGLIB_FPSCOUNTER_H

namespace Osaka{
	namespace RPGLib{

		class FPSCounter{
		public:
			FPSCounter();
			~FPSCounter();
			void _delete();
			void EndOfFrame();
		private:

		};
	}
}

#endif