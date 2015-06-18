 #include "stdafx.h"
#ifndef RPGLIB_TEXTUREMANAGER_H
#define RPGLIB_TEXTUREMANAGER_H
#include "rpglib_include.h"
#include "osaka_forward.h"
namespace Osaka{
	
	namespace RPGLib{
		
		class TextureManager{
		public:
			TextureManager(Factory* factory);
			~TextureManager();
			
			void SetSpritemaps(unorderedmap_spritemap_data& spritemaps, unorderedmap_spriteids_data& sprite_ids);
			void Init();
			void LoadTexture(const std::string& id);

			sprite_info CreateSprite(const std::string& id);
			/* Gives away ownership. Caller is responsible of deleting sprite_info */
			sprite_info* CreateSpriteRAWPointer(const std::string& id);
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner */
			Factory* factory;
			/* NOT Owner (list or spritemap_data) */
			unorderedmap_spritemap_data spritemaps;
			/* NOT Owner of the list (unordered_map*).
			 * This one holds which sprite_id is in which spritemap 
			 * hash=sprite_id, value=spritemap_id */
			unorderedmap_spriteids_data sprite_ids;
			/* Owner of all Textures */
			std::unordered_map<std::string, Engine::Texture*> textures;
		};
	}
}
#endif