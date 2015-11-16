// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 constants.h v1.0
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

//gameplay
const int GOBLIN_COUNT = 10;
const int BALL_COUNT = 50;
const float BOOM_TIME = 0.4;
const float ROATATION_SPEED = .0075;
const float MIN_GOBLIN_TIME = 0.2;
const float SCORE_POPUP_TIME = 1.0;
const int SCORE_DIVIDER = 20;
const int PRICE = 100;
const float RELOAD_UPGRADE = 0.05;
const int ARMOR_UPGRADE = 10;
const int BLAST_UPGRADE = 1;
const int RELOADING_IMAGE_COUNT = 50;

// graphic images
const char BKG_IMAGE[] = "pictures\\background.png";
const char GOBLIN_SHEET[] = "pictures\\goblin_sheet.png";
const char TOWER_100_HP_IMAGE[] = "pictures\\Tower.png";
const char TOWER_80_HP_IMAGE[] = "pictures\\Tower_damage1.png";
const char TOWER_60_HP_IMAGE[] = "pictures\\Tower_damage2.png";
const char TOWER_40_HP_IMAGE[] = "pictures\\Tower_damage3.png";
const char TOWER_20_HP_IMAGE[] = "pictures\\Tower_damage4.png";
const char CANNON_IMAGE[] = "pictures\\launcher.png";
const char POLE_IMAGE[] = "pictures\\pole.png";
const char CANNONBALL_SHEET[] = "pictures\\cannonball.png";
const char BOOM_SHEET[] = "pictures\\boom_sheet.png";
const char RELOADING_IMAGE[] = "pictures\\health.png";

   // time between frames of ship animation



// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

// audio cues
const char BOOM[] = "boom";
const char FIRE[] = "Tank";
const char BEEP[] = "beep1";

// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Spacewar";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1366;               // width of game in pixels
const UINT GAME_HEIGHT = 768;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations


// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key

//defines

#define BKG_IMAGE_SCALE 0.75
#define GOBLIN_IMAGE_SCALE 1.5
#define TOWER_IMAGE_SCALE 1.5
#define TOWER_BACK_SCALE 1.7
#define CANNON_IMAGE_SCALE 0.33
#define RELOADING_IMAGE_SCALE 0.33
#define POLE_IMAGE_SCALE 0.6
#define BALL_IMAGE_SCALE .15
#define BOOM_IMAGE_SCALE .25

//states
enum GameStates {startMenu, dirMenu, credMenu, gamePlay, store, end};



#endif
