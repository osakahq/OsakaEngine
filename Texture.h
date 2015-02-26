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
			Texture(SDL_Renderer& renderer, Debug::DebugPTR& d, IFileLoaderPTR& fileloader);
			~Texture();
			void _delete();

			void Load(const char* path, RGB_HEX& colorkey);
			void SetColor(Uint8 r, Uint8 g, Uint8 b);
			void SetAlpha(Uint8 a);
			void SetBlendingMode(SDL_BlendMode mode);

			int GetWeight();
			int GetHeight();

			/* This is the one you should call normally */
			void Render(const int x, const int y, const SDL_Rect& clip);

			//RenderCopyEx = expensive
			void RenderEx(const SDL_Rect& clip, const render_info_ex& info);

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
			IFileLoaderPTR fileloader;
			/* NOT Owner */
			Debug::DebugPTR debug;
		};
	}
}
#endif