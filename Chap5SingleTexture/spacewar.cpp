// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
#include "time.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar() {
	dxFontMedium = new TextDX();
	spawnCount = 0;
	
}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
	srand(10);
    Game::initialize(hwnd); // throws GameError

	//audio->playCue(BKG_MUSIC);

	srand(time(NULL));

	if (!bkgTexture.initialize(graphics, BKG_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bkg texture initialization failed"));
	if (!bkg.initialize(graphics, 0,0,0, &bkgTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	bkg.setX(0);
	bkg.setY(0);
	bkg.setScale(BKG_IMAGE_SCALE);

	if (!tower100Texture.initialize(graphics, TOWER_100_HP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bkg texture initialization failed"));
	if (!tower80Texture.initialize(graphics, TOWER_80_HP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bkg texture initialization failed"));
	if (!tower60Texture.initialize(graphics, TOWER_60_HP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bkg texture initialization failed"));
	if (!tower40Texture.initialize(graphics, TOWER_40_HP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bkg texture initialization failed"));
	if (!tower20Texture.initialize(graphics, TOWER_20_HP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bkg texture initialization failed"));

	if (!tower.initialize(this, 0,0,0, &tower100Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	tower.setActive(true);
	tower.setScale(TOWER_IMAGE_SCALE);

	if (!backTower.initialize(this, 0,0,0, &tower100Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	backTower.setActive(true);
	backTower.setX(-15);
	backTower.setY(300);
	backTower.setScale(TOWER_BACK_SCALE);

	if (!goblinTexture.initialize(graphics,GOBLIN_SHEET))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo texture"));

	for(int i = 0; i < GOBLIN_COUNT; i++){
		if (!goblins[i].initialize(this, goblinNS::WIDTH, goblinNS::HEIGHT, goblinNS::TEXTURE_COLS, &goblinTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo"));
		goblins[i].setScale(GOBLIN_IMAGE_SCALE);
		goblins[i].setActive(false);
		goblins[i].setVisible(false);
		goblins[i].setFrames(goblinNS::WALK_START_FRAME, goblinNS::WALK_END_FRAME);
		goblins[i].setCurrentFrame(goblinNS::WALK_START_FRAME);
		goblins[i].setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY);
	}

	if(dxFontMedium->initialize(graphics, 42, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	
	for(int i = 0; i < GOBLIN_COUNT; i++){
		goblins[i].update(frameTime);
	}

	int spawn = rand() % 300;

	if(spawn == 0 && spawnCount < GOBLIN_COUNT){
		goblins[spawnCount].setActive(true);
		goblins[spawnCount].setVisible(true);
		spawnCount += 1;
	}

	if (tower.getHealth() <= 20) tower.setTextureManager(&tower20Texture);
	else if (tower.getHealth() <= 40)tower.setTextureManager(&tower40Texture);
	else if (tower.getHealth() <= 60)tower.setTextureManager(&tower60Texture);
	else if (tower.getHealth() <= 80)tower.setTextureManager(&tower80Texture);

	// test damage
	// tower.setHealth(tower.getHealth() - .1);


}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
	VECTOR2 collisionVector;
	for(int i = 0; i < GOBLIN_COUNT; i++){
		if(goblins[i].collidesWith(tower, collisionVector)){
			goblins[i].atTower = true;
			goblins[i].setX(goblins[i].getX());
			goblins[i].setFrames(goblinNS::ATTACK_START_FRAME, goblinNS::ATTACK_END_FRAME);			
		}
	}


}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprite
	bkg.draw();

	tower.draw();
	backTower.draw();
	for(int i = 0; i < GOBLIN_COUNT; i++){
		goblins[i].draw();
	}

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	bkgTexture.onLostDevice();
	goblinTexture.onLostDevice();
	tower100Texture.onLostDevice();
	tower80Texture.onLostDevice();
	tower60Texture.onLostDevice();
	tower40Texture.onLostDevice();
	tower20Texture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
   
	bkgTexture.onResetDevice();
	goblinTexture.onResetDevice();
	tower100Texture.onResetDevice();
	tower80Texture.onResetDevice();
	tower60Texture.onResetDevice();
	tower40Texture.onResetDevice();
	tower20Texture.onResetDevice();

    Game::resetAll();
    return;
}


//void Spacewar::lose() {
//	if (!gameOverTexture.initialize(graphics, GAME_OVER_IMAGE))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Game over texture initialization failed"));
//	if (!gameOver.initialize(graphics, 0,0,0, &gameOverTexture))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init game over"));
//	gameOver.setX(0);
//	gameOver.setY(0);
//	gameOver.setScale(GAME_OVER_IMAGE_SCALE);
//}
//
//void Spacewar::win() {
//	if (!winTexture.initialize(graphics, WIN_IMAGE))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Game over texture initialization failed"));
//	if (!winScreen.initialize(graphics, 0,0,0, &winTexture))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init game over"));
//	winScreen.setX(0);
//	winScreen.setY(0);
//	winScreen.setScale(GAME_OVER_IMAGE_SCALE);
//	score += boat.getHealth() * 250;
//}