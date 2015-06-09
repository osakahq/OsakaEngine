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
#include "Square.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGFactory::RPGFactory(Debug::DebugPTR& debug, GameDataPTR& data, GameDataParamsPTR& gdp, FactoryPTR& factory){
			this->debug = debug;
			this->data = data;
			this->factory = factory;
			this->gamedataparams = gdp;

		}
		RPGFactory::~RPGFactory(){
			
		}
		void RPGFactory::_delete(){
			raw_renderer = NULL;
			debug = nullptr;
			data = nullptr;
			factory = nullptr;
			gamedataparams = nullptr;
		}
		void RPGFactory::Init(){
			//Be careful. This function is called BEFORE `app->Init()`
			raw_renderer = factory->app->sdl->GetRAWSDLRenderer();
		}
		ImagePTR RPGFactory::CreateImage(std::string id_sprite){
			return std::make_shared<Image>(raw_renderer, factory->texturem->CreateSpriteRAWPointer(id_sprite));
		}
		SquarePTR RPGFactory::CreateSquare(int x, int y, int h, int w){
			SquarePTR square = std::make_shared<Square>(raw_renderer);
			square->square.x = x;
			square->square.y = y;
			square->square.h = h;
			square->square.w = w;
			return square;
		}
		SquarePTR RPGFactory::CreateSquare(){
			return std::make_shared<Square>(raw_renderer);
		}
	}
}