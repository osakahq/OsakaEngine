 #include "stdafx.h"
#include "engine_include.h"
#include "gamedata_include.h"
#include "Texture.h"
#include "Debug.h"
#include "Factory.h"
#include "TextureManager.h"
namespace Osaka{
	namespace RPGLib{
		TextureManager::TextureManager(FactoryPTR& factory){
			this->factory = factory;
		}
		TextureManager::~TextureManager(){
#ifdef _DEBUG
			_CHECKDELETE("TextureManager");
#endif
		}
		void TextureManager::_delete(){
			for(auto it = textures.begin(); it != textures.end(); ++it )
				it->second->_delete();
			textures.clear();
			sprite_ids = nullptr;
			spritemaps = nullptr;
			factory = nullptr;
		}
		void TextureManager::SetSpritemaps(unorderedmap_spritemap_dataPTR& spritemaps, unorderedmap_spriteids_dataPTR& sprite_ids){
			this->spritemaps = spritemaps;
			this->sprite_ids = sprite_ids;
		}
		void TextureManager::Init(){
			Engine::TexturePTR texture;
			for( auto it = spritemaps->begin(); it!= spritemaps->end(); ++it ){
				texture = factory->CreateTexture();
				textures[it->first] = texture;
			}
		}
		/* This is called from AssetManager */
		void TextureManager::LoadTexture(const std::string id){
			spritemap_dataPTR spritemap = spritemaps->at(id);
			textures.at(id)->Load(spritemap->filename.c_str(), spritemap->colorkey);
		}

		void TextureManager::RenderSprite(const int x, const int y, const std::string& id){
			sprite_dataPTR sprite = sprite_ids->at(id);
			textures[sprite->belongs_to_texture]->Render(x, y, sprite->clip);
		}

		sprite_info TextureManager::CreateSprite(const std::string& id){
			sprite_dataPTR sprite = sprite_ids->at(id);
			return sprite_info(textures[sprite->belongs_to_texture].get()->GetRAWSDLTexture(), sprite->clip);
		}

		sprite_info* TextureManager::CreateSpriteRAWPointer(const std::string& id){
			sprite_dataPTR sprite = sprite_ids->at(id);
			return new sprite_info(textures[sprite->belongs_to_texture].get()->GetRAWSDLTexture(), sprite->clip);
		}

	}
}