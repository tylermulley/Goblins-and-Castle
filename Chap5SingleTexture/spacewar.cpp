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
	headingFont = new TextDX();
	highlightFont = new TextDX();
	spawnCount = 0;
	currentMenu = -1;
	gameOver = false;
	ballsShot = 0;
	currentShotX = 0;
	currentShotY = 0;
	cannonRadius = 0;

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

	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);

	lastMenu = new endMenu();
	lastMenu->initialize(graphics, input);

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

	if (!cannonBallTexture.initialize(graphics,CANNONBALL_SHEET))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo texture"));

	for(int i = 0; i < GOBLIN_COUNT; i++){
		if (!balls[i].initialize(this, cannonBallNS::WIDTH, cannonBallNS::HEIGHT, cannonBallNS::TEXTURE_COLS, &cannonBallTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo"));
		balls[i].setScale(BALL_IMAGE_SCALE);
		balls[i].setActive(false);
		balls[i].setVisible(false);
		balls[i].setFrames(cannonBallNS::START_FRAME, cannonBallNS::END_FRAME);
		balls[i].setCurrentFrame(cannonBallNS::START_FRAME);
		balls[i].setFrameDelay(cannonBallNS::BALL_ANIMATION_DELAY);
	}

	//booms
	/*for(int i = 0; i < GOBLIN_COUNT; i++){
		if (!balls[i].initialize(this, cannonBallNS::WIDTH, cannonBallNS::HEIGHT, cannonBallNS::TEXTURE_COLS, &cannonBallTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo"));
		balls[i].setScale(BALL_IMAGE_SCALE);
		balls[i].setActive(false);
		balls[i].setVisible(false);
		balls[i].setFrames(cannonBallNS::START_FRAME, cannonBallNS::END_FRAME);
		balls[i].setCurrentFrame(cannonBallNS::START_FRAME);
		balls[i].setFrameDelay(cannonBallNS::BALL_ANIMATION_DELAY);
	}*/

	if (!cannonTexture.initialize(graphics, CANNON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Cannon texture initialization failed"));
	if (!cannon.initialize(graphics, 0,0,0, &cannonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	cannon.setX(100);
	cannon.setY(240);
	cannon.setScale(CANNON_IMAGE_SCALE);
	cannonRadius = cannon.getCenterX() - cannon.getX();

	if (!poleTexture.initialize(graphics, POLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Cannon texture initialization failed"));
	if (!pole.initialize(graphics, 0,0,0, &poleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	pole.setX(167);
	pole.setY(260);
	pole.setScale(CANNON_IMAGE_SCALE);

	if(headingFont->initialize(graphics, 100, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	if(highlightFont->initialize(graphics, 70, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	highlightFont -> setFontColor(graphicsNS::RED);

	gameStates = startMenu;

    return;
}
void Spacewar::gameStateUpdate()
{
	if (mainMenu -> getSelectedItem() == 0){
		gameStates = gamePlay;
	}
	if (gameOver){
		gameStates = end;
	}
	
}
//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	int spawn;

	gameStateUpdate();
	switch (gameStates)
	{
	case startMenu:
		mainMenu->update();
		if (mainMenu -> getSelectedItem() == 0) currentMenu = 0;
		else if (mainMenu -> getSelectedItem() == 1) currentMenu = 1;
		else if (mainMenu -> getSelectedItem() == 2) currentMenu = 2;

		if(currentMenu == 1 || currentMenu == 2){
			if(input->wasKeyPressed(VK_ESCAPE)){
				currentMenu = -1;
			}
		}
		break;
	case gamePlay:

		//aim cannon 
		if(input->isKeyDown(VK_UP)){
			cannon.setRadians(cannon.getRadians() - ROATATION_SPEED);
		}
		else if(input->isKeyDown(VK_DOWN)){
			cannon.setRadians(cannon.getRadians() + ROATATION_SPEED);
		}

		//set radian restraints on cannon
		if(cannon.getRadians() > 1){
			cannon.setRadians(1);
		}
		if(cannon.getRadians() < -1){
			cannon.setRadians(-1);
		}

		currentShotX = cannon.getCenterX() + cannonRadius * cos(cannon.getRadians()) - (balls[0].getWidth()*BALL_IMAGE_SCALE)/2;
		currentShotY = cannon.getCenterY() + cannonRadius * sin(cannon.getRadians()) - (balls[0].getWidth()*BALL_IMAGE_SCALE)/2;

		cannonVector.x = currentShotX - cannon.getCenterX();
		cannonVector.y = cannon.getCenterY() - currentShotY;
		D3DXVec3Normalize(&cannonVector , &cannonVector);

		//shoot 
		if(ballsShot < GOBLIN_COUNT && input -> wasKeyPressed(VK_SPACE)){
			balls[ballsShot].setActive(true);
			balls[ballsShot].setVisible(true);
			balls[ballsShot].setX(currentShotX);
			balls[ballsShot].setY(currentShotY);
			ballsShot++;
		}

		//update balls position
		//v = v-initial + g * t 

		// update projectiles and goblins
		for(int i = 0; i < GOBLIN_COUNT; i++){
			goblins[i].senseDistance(tower.getX() + (tower.getWidth() * TOWER_IMAGE_SCALE));
			goblins[i].update(frameTime);
			balls[i].setBallMovement(cannonVector, frameTime);
		}

		spawn = rand() % 300;

		if(spawn == 0 && spawnCount < GOBLIN_COUNT){
			goblins[spawnCount].setX(GAME_WIDTH);
			goblins[spawnCount].setActive(true);
			goblins[spawnCount].setVisible(true);
			spawnCount += 1;
		}
		// test damage
		// tower.setHealth(tower.getHealth() - .1);

		if (tower.getHealth() <= 20) tower.setTextureManager(&tower20Texture);
		else if (tower.getHealth() <= 40)tower.setTextureManager(&tower40Texture);
		else if (tower.getHealth() <= 60)tower.setTextureManager(&tower60Texture);
		else if (tower.getHealth() <= 80)tower.setTextureManager(&tower80Texture);

		if(input -> isKeyDown(VK_TAB)){
			gameOver = true;
			currentMenu = -1;
		}

		// arctan(cannonHeightFromGround / gobDistToCastle)
		//cannon.setRadians(atan(tower.getHeight() * TOWER_IMAGE_SCALE / goblins[0].getDistance(tower.getWidth() + backTower.getWidth())));
		break;
	case end:
		lastMenu -> update();
		if (lastMenu -> getSelectedItem() == 0) currentMenu = 0;
		else if (lastMenu -> getSelectedItem() == 1) currentMenu = 1;
		else if (lastMenu -> getSelectedItem() == 2) currentMenu = 2;

		if(currentMenu == 1){
			if(input->wasKeyPressed(VK_ESCAPE)){
				currentMenu = -1;
			}
		}
		break;
	}
	
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
			goblins[i].setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY);
		}
	}

	for(int i = 0; i < GOBLIN_COUNT; i++){
		for(int j = 0; j < GOBLIN_COUNT; j++){
			if(balls[i].collidesWith(goblins[j], collisionVector)){
				goblins[j].setActive(false);
				goblins[j].setVisible(false);
			}
		}
	}


}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin(); 
	bkg.draw();

	switch(gameStates){
	case startMenu:
		if (currentMenu < 0) mainMenu -> displayMenu();
		else if (currentMenu == 1) {
			headingFont->print("Directions:", 360, 50);
			highlightFont->print("Press ESC to Return to Main Menu", 360, 480);
		}
		else if (currentMenu == 2) {
			headingFont->print("Credits:", 360, 50);
			highlightFont->print("Press ESC to Return to Main Menu", 360, 480);	
		}
		break;
	case gamePlay:
		tower.draw();
		pole.draw();
		backTower.draw();
		for(int i = 0; i < GOBLIN_COUNT; i++){
			balls[i].draw();
		}
		cannon.draw();
		for(int i = 0; i < GOBLIN_COUNT; i++){
			goblins[i].draw();
		}

		break;
	case end:
		if (currentMenu < 0) lastMenu -> displayMenu();
		else if (currentMenu == 0){
			gameStates = gamePlay;
			for(int i = 0; i < GOBLIN_COUNT; i++){
				goblins[i].setActive(false);
				goblins[i].setVisible(false);	
			}
			spawnCount = 0;
			currentMenu = -1;
			gameOver = false;
		}
		else if (currentMenu == 2) {
			PostQuitMessage(0);
		}
		else if (currentMenu == 1) {
			headingFont->print("Credits:", 360, 50);
			highlightFont->print("Press ESC to Return to Main Menu", 360, 480);
		}
		break;
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
	poleTexture.onLostDevice();
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
	poleTexture.onResetDevice();
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