// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "graphics.h"
#include "boom.h"
#include "textDX.h"
#include "goblin.h"
#include "tower.h"
#include "menu.h"
#include <sstream>
#include <string>
#include "endMenu.h"
#include "cannonBall.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:

	TextDX  *headingFont;
	TextDX  *highlightFont;
	int spawnCount;

	Menu *mainMenu;
	endMenu *lastMenu;
	std::string outString;
	// My defines

// My vars
	TextureManager bkgTexture;
	Image bkg;

	TextureManager poleTexture;
	Image pole;

	TextureManager cannonTexture;
	Image cannon;

	TextureManager tower100Texture;
	TextureManager tower80Texture;
	TextureManager tower60Texture;
	TextureManager tower40Texture;
	TextureManager tower20Texture;
	Tower tower;
	Tower backTower;

	TextureManager goblinTexture;
	Goblin goblins[GOBLIN_COUNT];

	TextureManager cannonBallTexture;
	cannonBall balls[GOBLIN_COUNT];

	int score;
	int currentMenu;
	int ballsShot;

	int currentShotX;
	int currentShotY;
	int cannonRadius;
	D3DXVECTOR3 cannonVector;

	bool gameOver;


	GameStates gameStates;
	

public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	void lose();
	void win();
	void gameStateUpdate();

};

//Stuff for physics


#endif
