#include "stdafx.h"
#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H
#include "osaka_forward.h"
namespace Osaka{
	
	namespace Engine{
		struct RGB_HEX;
		struct render_info;
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

			/*
			 * Optional parameters: angle, center. */
			void Render(int x, int y, SDL_Rect& clip, SDL_RendererFlip flip, double angle = 0.0, const SDL_Point* center = NULL);
			void Render(int x, int y, SDL_Rect& clip, double angle = 0.0, const SDL_Point* center = NULL);
			void Render(int x, int y, SDL_Rect& clip, double angle = 0.0, const SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
			void Render(const render_info& info);
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