 #include "stdafx.h"
#include "engine_include.h"
#include "gamedata_include.h"
#include "Texture.h"
#include "Debug.h"
#include "Factory.h"
#include "TextureManager.h"
namespace Osaka{
	namespace RPGLib{
		TextureManager::TextureManager(Factory* factory){
			this->factory = factory;
		}
		TextureManager::~TextureManager(){
#ifdef _DEBUG
			_CHECKDELETE("TextureManager");
#endif
			for(auto it = textures.begin(); it != textures.end(); ++it ){
				delete it->second;
			}
			textures.clear();
			sprite_ids.clear();
			spritemaps.clear();
			factory = NULL;
		}
		
		void TextureManager::SetSpritemaps(unorderedmap_spritemap_data& spritemaps, unorderedmap_spriteids_data& sprite_ids){
			this->spritemaps = spritemaps;
			this->sprite_ids = sprite_ids;
		}
		void TextureManager::Init(){
			for( auto it = spritemaps.begin(); it!= spritemaps.end(); ++it ){
				textures[it->first] = factory->CreateTexture();
			}
		}
		/* This is called from AssetManager */
		void TextureManager::LoadTexture(const std::string& id){
			spritemap_data* spritemap = spritemaps.at(id);
			textures.at(id)->Load(spritemap->filename.c_str(), spritemap->colorkey);
		}

		sprite_info TextureManager::CreateSprite(const std::string& id){
			sprite_data* sprite = sprite_ids.at(id);
			return sprite_info(textures[sprite->belongs_to_texture]->GetRAWSDLTexture(), sprite->clip, 0, 0);
		}

		sprite_info* TextureManager::CreateSpriteRAWPointer(const std::string& id){
			sprite_data* sprite = sprite_ids.at(id);
			return new sprite_info(textures[sprite->belongs_to_texture]->GetRAWSDLTexture(), sprite->clip, 0, 0);
		}

	}
}