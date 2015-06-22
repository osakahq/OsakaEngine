 #include "stdafx.h"
#ifndef OSAKA_FORWARD_H
#define OSAKA_FORWARD_H
namespace Osaka{
	namespace Component{
		class EventHandler;
		class EventArgs;
		class Registree;
		class Registry;
		class Callback;

		typedef std::shared_ptr<Registry>	RegistryPTR;
		typedef std::shared_ptr<Callback>	CallbackPTR;
	}
	namespace Network{
		class ServerConn;		
		class RecieveEventArgs;
	}
	namespace Debug{
		class Debug;			
		class Log;				
	}
	namespace Utils{
		
	}
	namespace Engine{
		class IFileLoader;			
		class DefaultFileLoader;	
		class PhysicsFSFileLoader;	

		class EScene;				
		class ESceneArgs;
		/* We still need this because it's difficult to find the owner if an ESceneArgs takes another ESceneArgs. */
		typedef std::shared_ptr<ESceneArgs>	ESceneArgsPTR;

		class Sound;				
		class SoundEffect;			
		class Music;				
		class EApplication;			
		class SDLLib;				
		class Texture;				
	}
	namespace RPGLib{
		class Factory;			
		class SceneFactory;		
		class GameDataLoader;	
		class GameData;			
		class GameDataParams;	
		class RPGApplication;	
		class RPGFactory;		
		class Settings;			
		class TextureManager;	

		class FontManager;		
		class StaticText;		

		class SoundManager;		

		class AssetManager;		
		class GameSession;		
		class GameSessionManager;	

		class Hiccups;
		class FPSCounter;		

		class RPGScene;			
		class SceneScript;		
		class Layer;			
		class LayerArgs;
		class Script;			
		class Canvas;			
		class UserInterface;	

		class Drawable;	
		class DrawableTexture;	
		class Square;	
		class Image;	
		class Effect;	
		class FadeInFadeOutEffect;	

		class OneLayer;			
		class OneLayerScene;	
		class OneLayerScript;	

		class FadeInOutScript;	
		class FadeInOutCanvas;
		class FadeInOutLayerArgs;

		class LoadingArgs;
		class LoadingSceneScript;
		class LoadingFadeCanvas;
		class LoadingFadeScript; 
		
		class InitScene;		
		class InitSceneArgs;	
		class DummyScene;		
		/*** SCENES *****/
		class PlaybackIntroSceneScript;	
		class PlaybackIntroCanvas;		
		class PlaybackIntroScript;		

		class StartMenuSceneScript;	
		class StartMenuScript;		
		class StartMenuCanvas;		
		/*****************************/
		
		class Ruler;			
		class TimeManager;		
		class Timer;			

		struct sound_data;		
		typedef std::unordered_map<std::string, sound_data*> unorderedmap_sound_data;

		struct spritemap_data;		
		typedef std::unordered_map<std::string, spritemap_data*> unorderedmap_spritemap_data;

		struct sprite_data;		
		typedef std::unordered_map<std::string, sprite_data*> unorderedmap_spriteids_data;

		struct gamesession_data;
		typedef std::unordered_map<std::string, gamesession_data*> unorderedmap_gamesession_data;

		struct asset_initload_data;	
		typedef std::unordered_map<std::string, asset_initload_data*> unorderedmap_asset_initload_data;
		typedef std::unordered_map<std::string, unsigned int> unorderedmap_assets_type;

		struct scene_data;
		struct related_scene_data;
		typedef std::unordered_map<std::string, scene_data*> unorderedmap_scene_data;
		
		struct fontcharacter_data;
		typedef std::unordered_map<char, fontcharacter_data*> unorderedmap_fontcharacter_data;
	}
}
#endif;