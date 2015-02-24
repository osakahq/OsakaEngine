#include "stdafx.h"
#include "gamedata_include.h"
#include "TextureManager.h"
#include "FontManager.h"

namespace Osaka{
	namespace RPGLib{
		FontManager::FontManager(TextureManagerPTR& texture, std::string _fontmap_error) : fontmap_error(_fontmap_error){
			fontmap = nullptr;
			this->texture = texture;
		}
		FontManager::~FontManager(){

		}
		void FontManager::_delete(){
			fontmap = nullptr;
			texture = nullptr;
		}
		void FontManager::SetFontmap(unorderedmap_fontcharacter_dataPTR& fontmap){
			this->fontmap = fontmap;
		}

		void FontManager::RenderText(const std::string text){

		}
	}
}