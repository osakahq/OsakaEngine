#include "stdafx.h"
#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H
#include "osaka_forward.h"
namespace Osaka{
	
	namespace Engine{
		struct RGB_HEX;
		struct render_info_ex;
		/* This class is technically a spritemap */
		class Texture {
		public:
			Texture(SDL_Renderer* renderer, Debug::Debug* d, IFileLoader* fileloader);
			~Texture();
			
			void Load(const char* path, RGB_HEX& colorkey);
			void SetColor(Uint8 r, Uint8 g, Uint8 b);
			void SetAlpha(Uint8 a);
			void SetBlendingMode(SDL_BlendMode mode);

			int GetWeight();
			int GetHeight();

			/* Doesn't give away ownership */
			SDL_Texture* GetRAWSDLTexture();
		/* ----------------------------------------------------------------------------------- */
		private:
			/* Owner */
			SDL_Texture* texture;
			int width;
			int height;

			/* NOT Owner */
			SDL_Renderer* renderer;
			/* NOT Owner */
			IFileLoader* fileloader;
			/* NOT Owner */
			Debug::Debug* debug;
		};
	}
}
#endif