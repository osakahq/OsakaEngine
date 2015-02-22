 #include "stdafx.h"

#ifndef RPGLIB_LOADINGUI_H
#define RPGLIB_LOADINGUI_H
#include "UserInterface.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		
		class LoadingUI : public UserInterface{
		public:
			LoadingUI(RPGApplicationPTR& app);
			~LoadingUI();
			void _delete();
			void Init();
			void Load();
			void Unload();
			void Show();
			void Hide();
			void StandBy();
			void Focus();
			void Update();
			void Draw();

			void Reset();
		private:
		};
	}
}

#endif