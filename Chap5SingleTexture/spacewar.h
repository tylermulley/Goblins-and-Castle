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

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:

	TextDX  *dxFontMedium;
	int spawnCount;

	// My defines

// My vars
	TextureManager bkgTexture;
	Image bkg;

	TextureManager tower100Texture;
	TextureManager tower80Texture;
	TextureManager tower60Texture;
	TextureManager tower40Texture;
	TextureManager tower20Texture;
	Tower tower;
	Tower backTower;

	TextureManager goblinTexture;
	Goblin goblins[GOBLIN_COUNT];

	int score;
	

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
};

//Stuff for physics


#endif
