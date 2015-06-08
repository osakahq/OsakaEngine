#include "stdafx.h"

#include "GameData.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "RPGApplication.h"
#include "SDLLib.h"
#include "Debug.h"
#include "TextureManager.h"
#include "Factory.h"
#include "RPGFactory.h"
#include "Image.h"
#include "osaka_forward.h"
namespace Osaka{
	namespace RPGLib{
		RPGFactory::RPGFactory(Debug::DebugPTR& debug, GameDataPTR& data, FactoryPTR& factory){
			this->debug = debug;
			this->data = data;
			this->factory = factory;
		}
		RPGFactory::~RPGFactory(){
			
		}
		void RPGFactory::_delete(){
			debug = nullptr;
			data = nullptr;
			factory = nullptr;
		}
		
		ImagePTR RPGFactory::CreateImage(std::string id_sprite){
			return std::make_shared<Image>(factory->app->sdl->GetRAWSDLRenderer(), factory->texturem->CreateSpriteRAWPointer(id_sprite));
		}
	}
}