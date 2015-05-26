 #include "stdafx.h"
#include "UserInterface.h"
#include "PlaybackIntroUI.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		PlaybackIntroUI::PlaybackIntroUI(RPGApplicationPTR& app) : UserInterface(app){
		}
		PlaybackIntroUI::~PlaybackIntroUI(){

		}
		void PlaybackIntroUI::_delete(){
			UserInterface::_delete();
		}
		
		void PlaybackIntroUI::Update(){
			
		}
		void PlaybackIntroUI::Draw(){
			
		}
	}
}