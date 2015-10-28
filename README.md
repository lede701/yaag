# Yet Another Ascii Game

This is an ASCII game engine that runs a semi role playing game I played as a child over the phone lines on Bulletin Board Systems (BBS).  This project was originated from a book I was reading about Game Patterns and I wanted to put these ideas into an engine that could be expanded.
The current state of this code is very unstable so don’t use this in a production environment!

## YAAG Programming Language

This engine has been written entirely in C++ using many OOP design patterns and some small memory optimizations.  Many tests have been performed on the core engine structures to make sure they are performing at optimal speeds based on my best knowledge.

## Graphics Engine

The base code is using an ASCII based graphic render engine that dumps text to the console on a Windows based computer.  The engine uses abstraction and sends all graphic requests to the graphics engine to handle the drawing of content to the end user.

The current engine design is to favor simulation over graphics so if the engine runs out of time in the simulation it will skip the rendering process for one frame but draw it on the next iteration.  Using a flag the engine will know if the simulation skipped drawing the last frame and then will skip simulating for that frame in order to update the output.

##The Game Portion

The game is currently melded into the core engine code which I have been working to move two a new project and make the core engine stand alone as a resource instead of being coupled to the engine.
The basic concept of the game currently is players fight in an Arena against monsters that vary in strength and capabilities.  The list of monster that players can fight are listed from weakest to strongest.  The current biggest winning factor in the game is player speed.  A slow player will typically lose to a faster player because they can’t get in the same number of hits per attack round.

##Networking

Currently all networking for the game engine is using the GameJolt API to connect and store all game data.  There is an option in the core game to switch between Jolt and using local database files.  The intention is to mix the two environments so that player data is stored locally but the game would retrieve the other data from Jolt.

The long term solution is to use a custom server that stores this on my website so that plaerys can track their ranking each month as they play the game.
