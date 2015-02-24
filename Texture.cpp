 #include "stdafx.h"
#include "Debug.h"
#include "engine_include.h"
#include "gamedata_include.h"
#include "IFileLoader.h"
#include "Texture.h"

namespace Osaka{
	namespace Engine{
		Texture::Texture(SDL_Renderer& renderer, Debug::DebugPTR& d, IFileLoaderPTR& fileloader){
			this->debug = d;
			this->renderer = &renderer;
			texture = NULL;
			width = 0;
			height = 0;

			this->fileloader = fileloader;
		}
		Texture::~Texture(){
#ifdef _DEBUG
			_CHECKDELETE("Texture");
#endif
			if( texture != NULL ){
				SDL_DestroyTexture(texture);
				texture = NULL;
			}
		}
		void Texture::_delete(){
			fileloader = nullptr;
			debug = nullptr;
		}
		void Texture::Load(const char* path, RGB_HEX& colorkey){
			if( texture != NULL ){
				debug->e("[Texture] Texture is already loaded.");
				return;
			}
			SDL_Texture* newTexture = NULL;
			SDL_Surface* loadedSurface = fileloader->LoadImageSurface(path);
			if( loadedSurface == NULL ){
				debug->e("[Texture] Unable to load image: "+std::string(path)+". Error: "+IMG_GetError());
			}
			//TODO: If you use a png with transparency, there is really no need to set the ColorKey
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, colorkey.r, colorkey.g, colorkey.b));
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

			if( newTexture == NULL ){
				debug->e("[Texture] Unable to create texture from: "+std::string(path)+". Error: "+SDL_GetError());
			}

			width = loadedSurface->w;
			height = loadedSurface->h;
			SDL_FreeSurface(loadedSurface);

			texture = newTexture;
		}
		void Texture::SetColor(Uint8 r, Uint8 g, Uint8 b){
			SDL_SetTextureColorMod(texture, r, g, b);
		}
		void Texture::SetAlpha(Uint8 a){
			SDL_SetTextureAlphaMod(texture, a);
		}
		void Texture::SetBlendingMode(SDL_BlendMode mode){
			SDL_SetTextureBlendMode(texture, mode);
		}

		void Texture::Render(const SDL_Rect& clip, const render_info& info){
			SDL_Rect renderQuad = {info.x, info.y, clip.w, clip.h};
			SDL_RenderCopyEx(renderer, texture, &clip, &renderQuad, info.angle, info.center, info.flip);
		}
		void Texture::Render(int x, int y, SDL_Rect& clip, double angle, const SDL_Point* center){
			//Optional: angle = 0.0, center = NULL
			SDL_Rect renderQuad = {x, y, clip.w, clip.h};
			SDL_RenderCopyEx(renderer, texture, &clip, &renderQuad, angle, center, SDL_FLIP_NONE);
		}
		void Texture::Render(int x, int y, SDL_Rect& clip, SDL_RendererFlip flip, double angle, const SDL_Point* center){
			//Optional: angle = 0.0, center = NULL
			SDL_Rect renderQuad = {x, y, clip.w, clip.h};
			SDL_RenderCopyEx(renderer, texture, &clip, &renderQuad, angle, center, flip);
		}
		void Texture::Render(int x, int y, SDL_Rect& clip, double angle, const SDL_Point* center, SDL_RendererFlip flip){
			//Optional: angle = 0.0, center = NULL, flip = SDL_FLIP_NONE
			SDL_Rect renderQuad = {x, y, clip.w, clip.h};
			SDL_RenderCopyEx(renderer, texture, &clip, &renderQuad, angle, center, flip);
		}
		
		int Texture::GetWeight(){
			return width;
		}
		int Texture::GetHeight(){
			return height;
		}
	}
}