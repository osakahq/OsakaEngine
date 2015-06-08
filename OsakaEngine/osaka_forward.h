 #include "stdafx.h"
#ifndef OSAKA_FORWARD_H
#define OSAKA_FORWARD_H
namespace Osaka{
	namespace Component{
		class EventHandler;		typedef std::shared_ptr<EventHandler> EventHandlerPTR;
		class EventArgs;
		//TODO: I need to modify EventHandler class if I want EventArgsPTR
		//class EventArgs;		typedef std::shared_ptr<EventArgs> EventArgsPTR;
	}
	namespace TestSuite{
		class RPGLibTestSuite;	typedef std::shared_ptr<RPGLibTestSuite> RPGLibTestSuitePTR;
	}
	namespace Network{
		class ServerConn;		typedef std::shared_ptr<ServerConn>		ServerConnPTR;
		class RecieveEventArgs; typedef std::shared_ptr<RecieveEventArgs> RecieveEventArgsPTR;
	}
	namespace Debug{
		class Debug;			typedef std::shared_ptr<Debug>			DebugPTR;
		class Log;				typedef std::shared_ptr<Log>			LogPTR;
	}
	namespace Utils{
		
	}
	namespace Engine{
		class IFileLoader;			typedef std::shared_ptr<IFileLoader>	IFileLoaderPTR;
		class DefaultFileLoader;	typedef std::shared_ptr<DefaultFileLoader>	DefaultFileLoaderPTR;
		class PhysicsFSFileLoader;	typedef std::shared_ptr<PhysicsFSFileLoader>PhysicsFSFileLoaderPTR;

		class EScene;				typedef std::shared_ptr<EScene>			EScenePTR;
		class ESceneArgs;		typedef std::shared_ptr<ESceneArgs>			ESceneArgsPTR;

		class Sound;				typedef std::shared_ptr<Sound>			SoundPTR;
		class SoundEffect;			typedef std::shared_ptr<SoundEffect>	SoundEffectPTR;
		class Music;				typedef std::shared_ptr<Music>			MusicPTR;
		class EApplication;			typedef std::shared_ptr<EApplication>	EApplicationPTR;
		class SDLLib;				typedef std::shared_ptr<SDLLib>			SDLLibPTR;
		class Texture;				typedef std::shared_ptr<Texture>		TexturePTR;
	}
	namespace RPGLib{
		class Factory;			typedef std::shared_ptr<Factory>		FactoryPTR;
		class SceneFactory;		typedef std::shared_ptr<SceneFactory>	SceneFactoryPTR;
		class GameDataLoader;	typedef std::shared_ptr<GameDataLoader> GameDataLoaderPTR;
		class GameData;			typedef std::shared_ptr<GameData>		GameDataPTR;
		class RPGApplication;	typedef std::shared_ptr<RPGApplication> RPGApplicationPTR;
		class RPGFactory;		typedef std::shared_ptr<RPGFactory>		RPGFactoryPTR;
		class Settings;			typedef std::shared_ptr<Settings>		SettingsPTR;
		class TextureManager;	typedef std::shared_ptr<TextureManager> TextureManagerPTR;

		class FontManager;		typedef std::shared_ptr<FontManager>	FontManagerPTR;
		class StaticText;		typedef std::shared_ptr<StaticText>		StaticTextPTR;

		class SoundManager;		typedef std::shared_ptr<SoundManager>	SoundManagerPTR;

		class AssetManager;		typedef std::shared_ptr<AssetManager>		AssetManagerPTR;
		class GameSession;		typedef std::shared_ptr<GameSession>		GameSessionPTR;
		class GameSessionManager;	typedef std::shared_ptr<GameSessionManager>GameSessionManagerPTR;

		class Hiccups;
		class FPSCounter;		typedef std::shared_ptr<FPSCounter>		FPSCounterPTR;

		class RPGScene;			typedef std::shared_ptr<RPGScene>		RPGScenePTR;
		class SceneScript;		typedef std::shared_ptr<SceneScript>	SceneScriptPTR;
		class Layer;			typedef std::shared_ptr<Layer>			LayerPTR;
		class LayerArgs;		typedef std::shared_ptr<LayerArgs>		LayerArgsPTR;
		class Script;			typedef std::shared_ptr<Script>			ScriptPTR;
		class Canvas;			typedef std::shared_ptr<Canvas>			CanvasPTR;
		class UserInterface;	typedef std::shared_ptr<UserInterface>	UserInterfacePTR;

		class Drawable;	typedef std::shared_ptr<Drawable>	DrawablePTR;
		class DrawableTexture;	typedef std::shared_ptr<DrawableTexture>	DrawableTexturePTR;
		class Square;	typedef std::shared_ptr<Square>	SquarePTR;
		class Image;	typedef std::shared_ptr<Image>	ImagePTR;
		class Effect;	typedef std::shared_ptr<Effect>	EffectPTR;
		class FadeInFadeOutEffect;	typedef std::shared_ptr<FadeInFadeOutEffect>	FadeInFadeOutEffectPTR;

		class OneLayer;			typedef std::shared_ptr<OneLayer>	OneLayerPTR;
		class OneLayerScene;	typedef std::shared_ptr<OneLayerScene>	OneLayerScenePTR;
		class OneLayerScript;	typedef std::shared_ptr<OneLayerScript> OneLayerScriptPTR;

		class FadeInOutScript;	typedef std::shared_ptr<FadeInOutScript> FadeInOutScriptPTR;
		class FadeInOutCanvas;	typedef std::shared_ptr<FadeInOutCanvas> FadeInOutCanvasPTR;

		class LoadingSceneScript;typedef std::shared_ptr<LoadingSceneScript>	LoadingSceneScriptPTR;
		class LoadingFadeCanvas;typedef std::shared_ptr<LoadingFadeCanvas>	LoadingFadeCanvasPTR;
		class LoadingFadeScript;typedef std::shared_ptr<LoadingFadeScript>	LoadingFadeScriptPTR;
		
		class InitScene;		typedef std::shared_ptr<InitScene>	InitScenePTR;
		class InitSceneArgs;	typedef std::shared_ptr<InitSceneArgs>	InitSceneArgsPTR;
		class DummyScene;		typedef std::shared_ptr<DummyScene>	DummyScenePTR;
		/*** SCENES *****/
		class PlaybackIntroSceneScript;	typedef std::shared_ptr<PlaybackIntroSceneScript>		PlaybackIntroSceneScriptPTR;
		class PlaybackIntroCanvas;		typedef std::shared_ptr<PlaybackIntroCanvas>		PlaybackIntroCanvasPTR;
		class PlaybackIntroScript;		typedef std::shared_ptr<PlaybackIntroScript>		PlaybackIntroScriptPTR;

		class StartMenuSceneScript;	typedef std::shared_ptr<StartMenuSceneScript>	StartMenuSceneScriptPTR;
		class StartMenuScript;		typedef std::shared_ptr<StartMenuScript>		StartMenuScriptPTR;
		class StartMenuCanvas;		typedef std::shared_ptr<StartMenuCanvas>		StartMenuCanvasPTR;
		/*****************************/
		
		class Ruler;			typedef std::shared_ptr<Ruler>	RulerPTR;
		class TimeManager;		typedef std::shared_ptr<TimeManager>	TimeManagerPTR;
		class Timer;			typedef std::shared_ptr<Timer>	TimerPTR;

		struct sound_data;		typedef std::shared_ptr<sound_data>												sound_dataPTR;
		/* Hash map */			typedef std::shared_ptr<std::unordered_map<std::string, sound_dataPTR>>			unorderedmap_sound_dataPTR;

		struct spritemap_data;	typedef std::shared_ptr<spritemap_data>											spritemap_dataPTR;
		/* Hash map */			typedef std::shared_ptr<std::unordered_map<std::string, spritemap_dataPTR>>		unorderedmap_spritemap_dataPTR;
		struct sprite_data;		typedef std::shared_ptr<sprite_data>											sprite_dataPTR;
		/* Hash map */			typedef std::shared_ptr<std::unordered_map<std::string, sprite_dataPTR>>		unorderedmap_spriteids_dataPTR;

		

		struct gamesession_data;typedef std::shared_ptr<gamesession_data>										gamesession_dataPTR;
		/* Hash map */			typedef std::shared_ptr<std::unordered_map<std::string, gamesession_dataPTR>>	unorderedmap_gamesession_dataPTR;

		struct asset_initload_data;		typedef std::shared_ptr<asset_initload_data>							asset_initload_dataPTR;
		/* Hash map */			typedef std::shared_ptr<std::unordered_map<std::string, asset_initload_dataPTR>> unorderedmap_asset_initload_dataPTR;

		typedef std::shared_ptr<std::unordered_map<std::string, unsigned int>> unorderedmap_assets_typePTR;

		struct scene_data;		typedef std::shared_ptr<scene_data>							scene_dataPTR;
		/* Hash map */			typedef std::shared_ptr<std::unordered_map<std::string, scene_dataPTR>> unorderedmap_scene_dataPTR;
		struct related_scene_data;
	
		struct fontcharacter_data;	typedef std::shared_ptr<fontcharacter_data>		fontcharacter_dataPTR;
		/* Hash map */				typedef std::shared_ptr<std::unordered_map<char, fontcharacter_dataPTR>> unorderedmap_fontcharacter_dataPTR;
	}
}
#endif;