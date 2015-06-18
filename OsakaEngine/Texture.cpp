 #include "stdafx.h"
#include "Debug.h"
#include "engine_include.h"
#include "gamedata_include.h"
#include "IFileLoader.h"
#include "Texture.h"

namespace Osaka{
	namespace Engine{
		Texture::Texture(SDL_Renderer* renderer, Debug::Debug* d, IFileLoader* fileloader){
			this->debug = d;
			this->renderer = renderer;
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
			renderer = NULL;
			fileloader = NULL;
			debug = NULL;
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

		SDL_Texture* Texture::GetRAWSDLTexture(){
			if( texture == NULL ){
				throw std::exception("[Texture] GetRAWSDLTexture > texture is NULL");
			}
			//Doesn't give away ownership
			return texture;
		}

		int Texture::GetWeight(){
			return width;
		}
		int Texture::GetHeight(){
			return height;
		}
	}
}