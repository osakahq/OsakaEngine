#include "stdafx.h"
#include "FontManager.h"

namespace Osaka{
	namespace RPGLib{
		FontManager::FontManager(){

		}
		FontManager::~FontManager(){

		}
		void FontManager::_delete(){

		}
		void FontManager::SetFontmap(std::unordered_map<std::string, fontcharacter_data*>& fontmap){
			this->fontmap = &fontmap;
		}
	}
}