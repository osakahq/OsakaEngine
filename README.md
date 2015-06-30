#OSAKA ENGINE

### Description:
This is a simple C++ 2D RPG Engine using **SDL** (https://www.libsdl.org/). It also includes the use of **PhysFS** (http://icculus.org/physfs/) for the archived file subsystem. Library for reading XML files: **rapidxml** (http://sourceforge.net/projects/rapidxml/)

### Work in progress:
Osaka Engine is in an early alpha stage (game wise), most of the base of the engine itself is completed.
 - Game: 5%~ completed
 - Engine: 60%~ completed

Next development milestone: User interface.

### Compile info (Win x86)
Visual studio 2012 Version 11.0.61030.00 Update 4 (Windows 7)  
SDL 2.0.3  
PhysFS 2.0.3  (Compiled using CMake and VS Studio 2012)  

### Engine Features (highlights):
 - Texture map loading (sprites)
 - Font sprites
 - Lag indicator (FPS wise)
 - Virtual sync or a custom FPS cap.
 - Dynamic asynchronous (multi thread) asset loading and unloading
 - Network debugging (including variables indicators, logging and commands)
 - Frame pausing (DEBUG only)
 - Scene-driven (events and callbacks)
 - Dynamic scene loading while the game is running when debugging (DLL)
 - Direct file loading or PhysFS file loader.
 - Flexible (custom scenes, custom drawable objects, effects, etc.)
 - A Test suite (integration tests)
 - A catching up method if a frame took longer than the target delta time per frame.

### Overview (How the engine works)
**Disclaimer**: I wish I had enough time to properly update and explain in a detailed way how the engine works. But for now, these diagrams have to suffice.
Made with Draw.io (https://www.draw.io/)

Initialization / Loop: http://i.imgur.com/BAs8H5p.png  
How scenes are constructed (creation): http://i.imgur.com/LiinED1.png  
Scene/Layer dependency: http://i.imgur.com/21Ul4BZ.png  
Album: http://imgur.com/a/t2Ymp  

### Scene driven
The game (not the engine) is basically made up of `Scenes`, and `Scenes` are made up of `Layers` and one `MainSceneScript`, and Layers can be made of 3 underlying objects (up to the developer): `Script`, `Canvas` and `UI`. 

For example: When the game starts, it will start with the `IntroScene` scene, which inside has only one `Layer`, which has a `Canvas` object. `Canvas` is responsible of creating and drawing the intro images (OsakaEngine logo, Gamestudio logo, etc.) and also responsible of switching to the next scene, which is `StartMenuScene`.

`Scenes` can be stacked. `Layers` can also be stacked. Example of the difference between `Scenes` and `Layers`:
 - `TownMapScene` has 2 layers. `LayerGame` and `LayerMap`
  - `LayerGame` has an `UI` object which is responsible of drawing the text (HP, MP, gold, etc.)
  - `LayerMap` has a `Canvas` object which is responsible of drawing the map (tiles), characters, etc.

