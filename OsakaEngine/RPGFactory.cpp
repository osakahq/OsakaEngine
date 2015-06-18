#include "stdafx.h"

#include "GameData.h"
#include "GameDataParams.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "RPGApplication.h"
#include "SDLLib.h"
#include "Debug.h"
#include "TextureManager.h"
#include "Factory.h"
#include "RPGFactory.h"
#include "Image.h"
#include "FadeInFadeOutEffect.h"
#include "Square.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGFactory::RPGFactory(Debug::Debug* debug, GameData* data, GameDataParams* gdp, Factory* factory){
			this->debug = debug;
			this->data = data;
			this->factory = factory;
			this->gamedataparams = gdp;

		}
		RPGFactory::~RPGFactory(){
			raw_renderer = NULL;
			debug = NULL;
			data = NULL;
			factory = NULL;
			gamedataparams = NULL;
		}
		
		void RPGFactory::Init(){
			//Be careful. This function is called BEFORE `app->Init()`
			raw_renderer = factory->app->sdl->GetRAWSDLRenderer();
		}
		Image* RPGFactory::CreateImage(const std::string& id_sprite){
			return new Image(raw_renderer, factory->texturem->CreateSpriteRAWPointer(id_sprite));
		}
		Square* RPGFactory::CreateSquare(int x, int y, int h, int w){
			Square* square = new Square(raw_renderer);
			square->square.x = x;
			square->square.y = y;
			square->square.h = h;
			square->square.w = w;
			return square;
		}
		Square* RPGFactory::CreateSquare(){
			return new Square(raw_renderer);
		}
		FadeInFadeOutEffect* RPGFactory::CreateFadeInFadeOutEffect(){
			return new FadeInFadeOutEffect(factory->CreateTimer());
		}
	}
}