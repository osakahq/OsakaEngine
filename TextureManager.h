 #include "stdafx.h"
#ifndef RPGLIB_TEXTUREMANAGER_H
#define RPGLIB_TEXTUREMANAGER_H
#include "rpglib_include.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace Engine{
		struct render_info_ex;
	}
	namespace RPGLib{
		
		class TextureManager{
		public:
			TextureManager(FactoryPTR& factory);
			~TextureManager();
			void _delete();
			void SetSpritemaps(unorderedmap_spritemap_dataPTR& spritemaps, unorderedmap_spriteids_dataPTR& sprite_ids);
			void LoadTexture(const std::string id);

			void RenderSprite(const int x, const int y, const std::string& id);

			sprite_info CreateSprite(const std::string& id);
			/* Gives away ownership. Caller is responsible of deleting sprite_info */
			sprite_info* CreateSpriteRAWPointer(const std::string& id);
		/* ----------------------------------------------------------------------------------- */
		private:
			/* NOT Owner */
			FactoryPTR factory;
			/* NOT Owner (list or spritemap_data) */
			unorderedmap_spritemap_dataPTR spritemaps;
			/* NOT Owner of the list (unordered_map*).
			 * This one holds which sprite_id is in which spritemap 
			 * hash=sprite_id, value=spritemap_id */
			unorderedmap_spriteids_dataPTR sprite_ids;
			/* Owner of all Textures */
			std::unordered_map<std::string, Engine::TexturePTR> textures;
		};
	}
}
#endif