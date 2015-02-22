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

			Engine::TexturePTR texture;
			for( auto it = spritemaps->begin(); it!= spritemaps->end(); ++it ){
				texture = factory->CreateTexture();
				//texture->Load(it->second->filename.c_str(), it->second->colorkey);
				textures[it->first] = texture;
			}
		}
		void TextureManager::LoadTexture(const std::string id){
			spritemap_dataPTR spritemap = spritemaps->at(id);
			textures.at(id)->Load(spritemap->filename.c_str(), spritemap->colorkey);
		}

		void TextureManager::RenderSprite(const std::string& id, const Engine::render_info& render){
			textures[sprite_ids->at(id)]->Render(render);
		}
	}
}