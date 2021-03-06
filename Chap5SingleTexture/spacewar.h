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
#include "storeMenu.h"
#include <sstream>
#include <string>
#include "endMenu.h"
#include "cannonBall.h"
#include "reloadBar.h"

struct ScorePopup {
	int x;
	float timer;
};

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:

	void resetGame();

	TextDX  *headingFont;
	TextDX  *highlightFont;
	TextDX  *smallFont;
	TextDX	*scorePopupFont;
	TextDX	*negPointsFont;

	Menu *mainMenu;
	StoreMenu *storeMenu;
	endMenu *lastMenu;
	std::string outString;
	// My defines

// My vars
	TextureManager bkgTexture;
	Image bkg;

	TextureManager cloudTexture;
	Image clouds[CLOUD_COUNT];

	TextureManager splashTexture;
	Image splash;

	TextureManager poleTexture;
	Image pole;

	TextureManager cannonTexture;
	Image cannon;

	TextureManager bossHealthTexture;
	Image bossHealth[HEALTH_IMAGE_COUNT];

	TextureManager tower100Texture;
	TextureManager tower80Texture;
	TextureManager tower60Texture;
	TextureManager tower40Texture;
	TextureManager tower20Texture;
	Tower tower;
	Tower backTower;

	TextureManager goblinTexture;
	Goblin goblins[GOBLIN_COUNT];
	Goblin boss;

	TextureManager cannonBallTexture;
	cannonBall balls[BALL_COUNT];

	TextureManager boomTexture;
	Boom booms[BALL_COUNT];

	TextureManager nukeTexture;
	Image nuke;

	//TextureManager reloadBarTexture;
	//ReloadBar bar;

	float splashTimer;

	int score;
	int level;

	int currentMenu;

	int ballsShot;
	int boomsUsed;

	float reloadTimer;
	bool reloadSoundPlayed;
	float goblinTimer;

	ScorePopup scorePopups[GOBLIN_COUNT];

	int pointsToLose;
	int pointsJustLost;
	float negPointsTimer;

	int currentShotX;
	int currentShotY;
	int cannonRadius;

	int spawnCount;
	int killCount;

	bool nuking;

	float RELOAD_TIME;
	int FULL_HEALTH;
	
	VECTOR2 cannonVector;
	VECTOR2 particleVector;
	VECTOR2 particleSpeed;

	GameStates gameStates;

	float particleYOffset;
	float particleXOffset;

	float timeInBetween;
	int inBetweenCount;

	int upgrade1;
	int upgrade2;
	int upgrade3;
	
	int boomOffSetX;
	int boomOffSetY;

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
	void displayBoom(int x, int y);

};

//Stuff for physics


#endif
