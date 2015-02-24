 #include "stdafx.h"
#ifndef OSAKA_FORWARD_H
#define OSAKA_FORWARD_H
namespace Osaka{
	namespace Component{
		class EventHandler;		typedef std::shared_ptr<EventHandler> EventHandlerPTR;
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
	namespace Engine{
		class EScenePassParams;		typedef std::shared_ptr<EScenePassParams> EScenePassParamsPTR;

		class IFileLoader;			typedef std::shared_ptr<IFileLoader>	IFileLoaderPTR;
		class DefaultFileLoader;	typedef std::shared_ptr<DefaultFileLoader>	DefaultFileLoaderPTR;
		class PhysicsFSFileLoader;	typedef std::shared_ptr<PhysicsFSFileLoader>PhysicsFSFileLoaderPTR;

		class EScene;				typedef std::shared_ptr<EScene>				EScenePTR;
		class EScenePassParams;		typedef std::shared_ptr<EScenePassParams>	EScenePassParamsPTR;

		class Sound;				typedef std::shared_ptr<Sound>			SoundPTR;
		class SoundEffect;			typedef std::shared_ptr<SoundEffect>	SoundEffectPTR;
		class Music;				typedef std::shared_ptr<Music>			MusicPTR;
		class EApplication;			typedef std::shared_ptr<EApplication>	EApplicationPTR;
		class SDLLib;				typedef std::shared_ptr<SDLLib>			SDLLibPTR;
		class Texture;				typedef std::shared_ptr<Texture>		TexturePTR;
	}
	namespace RPGLib{
		class Factory;			typedef std::shared_ptr<Factory>		FactoryPTR;
		class GameDataLoader;	typedef std::shared_ptr<GameDataLoader> GameDataLoaderPTR;
		class GameData;			typedef std::shared_ptr<GameData>		GameDataPTR;
		class RPGApplication;	typedef std::shared_ptr<RPGApplication> RPGApplicationPTR;
		class RPGFactory;		typedef std::shared_ptr<RPGFactory>		RPGFactoryPTR;
		class Settings;			typedef std::shared_ptr<Settings>		SettingsPTR;
		class TextureManager;	typedef std::shared_ptr<TextureManager> TextureManagerPTR;
		class FontManager;		typedef std::shared_ptr<FontManager>	FontManagerPTR;
		class SoundManager;		typedef std::shared_ptr<SoundManager>	SoundManagerPTR;

		class AssetManager;		typedef std::shared_ptr<AssetManager>		AssetManagerPTR;
		class GameSession;		typedef std::shared_ptr<GameSession>		GameSessionPTR;
		class GameSessionManager;	typedef std::shared_ptr<GameSessionManager>GameSessionManagerPTR;

		class FPSCounter;		typedef std::shared_ptr<FPSCounter>		FPSCounterPTR;

		class RPGScene;			typedef std::shared_ptr<RPGScene>		RPGScenePTR;
		class Canvas;			typedef std::shared_ptr<Canvas>			CanvasPTR;
		class Script;			typedef std::shared_ptr<Script>			ScriptPTR;
		class UserInterface;	typedef std::shared_ptr<UserInterface>	UserInterfacePTR;

		class LoadingCanvas;	typedef std::shared_ptr<LoadingCanvas>		LoadingCanvasPTR;
		class LoadingScript;	typedef std::shared_ptr<LoadingScript>		LoadingScriptPTR;
		class LoadingUI;		typedef std::shared_ptr<LoadingUI>			LoadingUIPTR;
		class RPGLoadingScene;	typedef std::shared_ptr<RPGLoadingScene>	RPGLoadingScenePTR;

		/*** SCENES *****/
		class PlaybackIntroCanvas;	typedef std::shared_ptr<PlaybackIntroCanvas>		PlaybackIntroCanvasPTR;
		class PlaybackIntroScript;	typedef std::shared_ptr<PlaybackIntroScript>		PlaybackIntroScriptPTR;
		class PlaybackIntroUI;		typedef std::shared_ptr<PlaybackIntroUI>			PlaybackIntroUIPTR;
		/*****************************/
		
		class Ruler;			typedef std::shared_ptr<Ruler>	RulerPTR;
		class TimeManager;		typedef std::shared_ptr<TimeManager>	TimeManagerPTR;
		class Timer;			typedef std::shared_ptr<Timer>	TimerPTR;

		struct sound_data;		typedef std::shared_ptr<sound_data>												sound_dataPTR;
		/*Hash map*/			typedef std::shared_ptr<std::unordered_map<std::string, sound_dataPTR>>			unorderedmap_sound_dataPTR;

		struct spritemap_data;	typedef std::shared_ptr<spritemap_data>											spritemap_dataPTR;
		/*Hash map*/			typedef std::shared_ptr<std::unordered_map<std::string, spritemap_dataPTR>>		unorderedmap_spritemap_dataPTR;
		/*Hash map*/			typedef std::shared_ptr<std::unordered_map<std::string, std::string>>			unorderedmap_spriteids_dataPTR;
		
		struct gamesession_data;typedef std::shared_ptr<gamesession_data>										gamesession_dataPTR;
		/*Hash map*/			typedef std::shared_ptr<std::unordered_map<std::string, gamesession_dataPTR>>	unorderedmap_gamesession_dataPTR;

		struct asset_initload_data;		typedef std::shared_ptr<asset_initload_data>							asset_initload_dataPTR;
		/*Hash map*/			typedef std::shared_ptr<std::unordered_map<std::string, asset_initload_dataPTR>> unorderedmap_asset_initload_dataPTR;

		typedef std::shared_ptr<std::unordered_map<std::string, unsigned int>> unorderedmap_assets_typePTR;

		struct scene_data;		typedef std::shared_ptr<scene_data>							scene_dataPTR;
		/*Hash map*/			typedef std::shared_ptr<std::unordered_map<std::string, scene_dataPTR>> unorderedmap_scene_dataPTR;
		struct related_scene_data;
	
	}
}
#endif;