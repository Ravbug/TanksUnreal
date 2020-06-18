# TanksUnreal
![Screenshot of the game](https://camo.githubusercontent.com/7dea6a30aa2528dac89820aab3e016583550415d/68747470733a2f2f692e696d6775722e636f6d2f6f7a706e6a455a2e706e67)

## About
This repository contains my implementation of the [Unity Tanks! Tutorial game](https://unity3d.com/learn/tutorials/s/tanks-tutorial) in [Unreal Engine](https://www.unrealengine.com/), the engine behind the popular game [Fortnite](http://fortnite.com/). 
I am writing the game predominantly in C++, using blueprint subclassing where it's easier. The goal of this project is to illustrate the methods for creating a shared local multiplayer game in Unreal Engine, and to provied a common project for comparing Unity and Unreal.

## Requirements:
Software
1. Engine: [Unreal Engine 4.24.3](https://www.unrealengine.com/en-US/eulacheck?state=https%3A%2F%2Fwww.unrealengine.com%2Fen-US%2Ffeed&studio=false) or newer
2. IDE: [Microsoft Visual Studio Community 2017](https://visualstudio.microsoft.com/) or [Xcode](https://developer.apple.com/xcode/) 
   - The editor works on Linux, but Linux users must configure their environment to their specific system.

Hardware
1. A system that meets the [Unreal Editor requirements](https://docs.unrealengine.com/en-US/GettingStarted/RecommendedSpecifications/index.html)
2. For Raytracing, a GPU that supports DirectX Ray Tracing.

## Compiling it yourself
1. Ensure you have the software listed above installed on your computer.
2. Download this repository as a zip or clone with --depth=1
### Editor only
4. Open the `.uproject` and compile now if it asks
5. Play! 
### From IDE
4. Right-click the `.uproject` file in the Finder/File Explorer and press `Generate Xcode/Visual Studio Project`
   - If this option is not visible, open the `.uproject` and go to `File->Generate Xcode/Visual Studio Project`
5. Press the Compile and Run button in your IDE (CMD+R in Xcode, green Run button in VS)
6. Play!

## Just want to play the game?
Head over to the [Releases](https://github.com/Ravbug/TanksUnreal/releases) section and download the latest. Linux users must create a build for their system, instructions are on the release page.

**Packaged game supported platforms** 
- macOS
- Windows (+ DXR if applicable)
- Linux (Vulkan only)
- iOS*
- Android* 

\* You must create a build for this platform using the editor

## Issues
If you find an issue, use the [Issues](https://github.com/Ravbug/TanksUE4/issues) section of this repository to report it. Be sure to include specifically what the issue is, as well as what you've done to try to fix it. The more information you include, the better. However, I may not be able to fix it quickly.

## Tasks
- [x] Correct shared camera 
- [x] Input using playercontrollers
- [x] Title screen
- [x] Tank Physics
- [x] Build level
- [x] Set up lightmass and scene lighting
- [x] Barebones AI
- [x] Fix naming system
- [x] Tank Colors
- [x] Graphics Settings
~~- [ ] Networking support~~
- [x] Mobile Touch
- [x] points to win
