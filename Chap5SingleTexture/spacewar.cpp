// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
#include "time.h"
#include <string>
#include "particleManager.h"

ParticleManager pm;

using std::string;

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar() {
	headingFont = new TextDX();
	highlightFont = new TextDX();
	scorePopupFont = new TextDX();
	negPointsFont = new TextDX();
	smallFont = new TextDX();

	splashTimer = 0;

	RELOAD_TIME = 1.4;
	//RELOAD_TIME = .05;
	FULL_HEALTH = 100;

	spawnCount = 0;
	currentMenu = -1;
	ballsShot = 0;
	currentShotX = 0;
	currentShotY = 0;
	cannonRadius = 0;
	boomsUsed = 0;
	reloadTimer = RELOAD_TIME;
	goblinTimer = MIN_GOBLIN_TIME;

	score = 0;
	level = 1;

	pointsToLose = 0;
	pointsJustLost = 0;
	negPointsTimer = SCORE_POPUP_TIME;
	killCount = 0;

	nuking = false;

	particleYOffset = 0;
	particleXOffset = 10;

	timeInBetween = 0;
	inBetweenCount = 0;

	upgrade1 = 0;
	upgrade2 = 0;
	upgrade3 = 0;

	boomOffSetX = 0;
	boomOffSetY = 0;
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
	mainMenu->initialize(this, graphics, input);

	storeMenu = new StoreMenu();
	storeMenu->initialize(this, graphics, input);

	lastMenu = new endMenu();
	lastMenu->initialize(graphics, input);

	audio->playCue(BKG_MUSIC);

	srand(time(NULL));

	pm.initialize(graphics);

	if (!bkgTexture.initialize(graphics, BKG_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bkg texture initialization failed"));
	if (!bkg.initialize(graphics, 0,0,0, &bkgTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	bkg.setX(0);
	bkg.setY(0);
	bkg.setScale(BKG_IMAGE_SCALE);

	if (!splashTexture.initialize(graphics, SPLASH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Splash texture initialization failed"));
	if (!splash.initialize(graphics, 0,0,0, &splashTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init splash"));
	splash.setX(0);
	splash.setY(0);
	splash.setScale(SPLASH_IMAGE_SCALE);

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

	if (!boss.initialize(this, goblinNS::WIDTH, goblinNS::HEIGHT, goblinNS::TEXTURE_COLS, &goblinTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo"));
	boss.setScale(BOSS_IMAGE_SCALE);
	boss.setVisible(false);
	boss.setActive(false);
	boss.setX(GAME_WIDTH);
	boss.setVelocity(VECTOR2(-goblinNS::BOSS_SPEED,0));
	boss.setY(133);
	boss.setFrames(goblinNS::WALK_START_FRAME, goblinNS::WALK_END_FRAME);
	boss.setCurrentFrame(goblinNS::WALK_START_FRAME);
	boss.setFrameDelay(goblinNS::BOSS_ANIMATION_DELAY);
	boss.isBoss = true;
	boss.setHealth(BOSS_HP);

	if (!cannonBallTexture.initialize(graphics,CANNONBALL_SHEET))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo texture"));

	for(int i = 0; i < BALL_COUNT; i++){
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
	if (!boomTexture.initialize(graphics,BOOM_SHEET))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo texture"));

	for(int i = 0; i < BALL_COUNT; i++){
		if (!booms[i].initialize(this, boomNS::WIDTH, boomNS::HEIGHT, boomNS::TEXTURE_COLS, &boomTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jpo"));
		booms[i].setScale(BOOM_IMAGE_SCALE);
		booms[i].setActive(false);
		booms[i].setVisible(false);
		booms[i].setFrames(boomNS::START_FRAME, boomNS::END_FRAME);
		booms[i].setCurrentFrame(boomNS::START_FRAME);
		booms[i].setFrameDelay(boomNS::BOOM_ANIMATION_DELAY);
		booms[i].setX(-2 * GAME_WIDTH);
		booms[i].setY(-2 * GAME_HEIGHT);
	}

	if (!cannonTexture.initialize(graphics, CANNON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Cannon texture initialization failed"));
	if (!cannon.initialize(graphics, 670, 151, 1, &cannonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	cannon.setCurrentFrame(19);
	cannon.setFrameDelay(RELOAD_TIME / 20);
	cannon.setX(90);
	cannon.setY(230);
	cannon.setScale(CANNON_IMAGE_SCALE);
	cannonRadius = cannon.getCenterX() - cannon.getX();

	if (!poleTexture.initialize(graphics, POLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Cannon texture initialization failed"));
	if (!pole.initialize(graphics, 0,0,0, &poleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	pole.setX(167);
	pole.setY(260);
	pole.setScale(POLE_IMAGE_SCALE);

	if (!nukeTexture.initialize(graphics, NUKE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Nuke texture initialization failed"));
	if (!nuke.initialize(graphics, 0,0,0, &nukeTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init nuke"));
	nuke.setX(GAME_WIDTH / 2 - nuke.getWidth() * NUKE_IMAGE_SCALE / 2);
	nuke.setY(-nuke.getHeight() * NUKE_IMAGE_SCALE);
	nuke.setScale(NUKE_IMAGE_SCALE);
	nuke.setVisible(false);

	if(headingFont->initialize(graphics, 100, true, false, "Segoe Marker") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	if(highlightFont->initialize(graphics, 70, true, false, "Segoe Marker") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	highlightFont -> setFontColor(graphicsNS::RED);

	if(scorePopupFont->initialize(graphics, 28, true, false, "Segoe Marker") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	scorePopupFont -> setFontColor(graphicsNS::GREEN);

	if(negPointsFont->initialize(graphics, 34, true, false, "Segoe Marker") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	negPointsFont -> setFontColor(graphicsNS::RED);

	if(smallFont->initialize(graphics, 50, true, false, "Segoe Marker") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	smallFont -> setFontColor(graphicsNS::WHITE);

	gameStates = startMenu;

    return;
}
void createParticleEffect(VECTOR2 pos, VECTOR2 vel, int numParticles){
	
	pm.setPosition(pos);
	pm.setVelocity(vel);
	pm.setVisibleNParticles(numParticles);

}
void Spacewar::gameStateUpdate()
{
	//gameStates = bossFight;
	//gameStates = store;
	if (gameStates == startMenu && mainMenu -> getSelectedItem() == 0){
		resetGame();
		gameStates = inBetween;
	}
	if (killCount >= GOBLIN_COUNT) { // reset everything
		audio->playCue(BOOM);
		resetGame();
		if (level == 3) {
			gameStates = inBetween;
			inBetweenCount++;
			timeInBetween = 0;
			killCount = 0;
		}
		else {
			gameStates = inBetween;
			inBetweenCount++;
			timeInBetween = 0;
			killCount = 0;
		}
	}
	if(gameStates == store) {
		if(input->isKeyDown(VK_ESCAPE)){
			level++;
			gameStates = inBetween;
			inBetweenCount++;
			timeInBetween = 0;
		}
	}

	if(gameStates == inBetween && timeInBetween > 3 && inBetweenCount % 2 == 0 && level == 4){
		gameStates = bossFight;
		tower.setHealth(FULL_HEALTH);
	}
	else if(gameStates == inBetween && timeInBetween > 3 && inBetweenCount % 2 != 0){
		gameStates = store;
	}
	else if(gameStates == inBetween && timeInBetween > 3 && inBetweenCount % 2 == 0){
		gameStates = gamePlay;
		tower.setHealth(FULL_HEALTH);
	}

	if(gameStates == gamePlay && tower.getHealth() <= 0) {
		resetGame();
		level = 1;
		currentMenu = -1;
		gameStates = end;
	}
	if(gameStates == bossFight && boss.getHealth() <= 0){
		level = 1;
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
	case inBetween:

		break;
	case gamePlay:
		//aim cannon 
		if(input->isKeyDown(VK_UP)){
			if(cannon.getRadians() > -1){
				cannon.setRadians(cannon.getRadians() - ROATATION_SPEED);
			}

		}
		else if(input->isKeyDown(VK_DOWN)){
			if(cannon.getRadians() < 1){
				cannon.setRadians(cannon.getRadians() + ROATATION_SPEED);				
			}

		}

		// reset balls shot if all balls shot
		if (ballsShot >= BALL_COUNT){
				ballsShot = 0;
		} 

		//shoot 
		reloadTimer += frameTime;
		if(input -> wasKeyPressed(VK_SPACE) && reloadTimer >= RELOAD_TIME && ballsShot < BALL_COUNT && balls[ballsShot].getActive() == false){

			//starting ball position
			currentShotX = cannon.getCenterX() + cannonRadius * cos(cannon.getRadians()) - (balls[0].getWidth()*BALL_IMAGE_SCALE)/2;
			currentShotY = cannon.getCenterY() + cannonRadius * sin(cannon.getRadians()) - (balls[0].getWidth()*BALL_IMAGE_SCALE)/2;
			//angle of the shot
			cannonVector.x = cos(cannon.getRadians());
			cannonVector.y = sin(cannon.getRadians()) * 1.25;
			D3DXVec2Normalize(&cannonVector , &cannonVector);

			// particle stuff
			particleVector.x = currentShotX + particleXOffset;
			particleVector.y = currentShotY + particleYOffset;
			particleSpeed = VECTOR2(cannonVector.x * 300, cannonVector.y * 300);

			audio->playCue(FIRE); 
			pm.rotateImage(cannon.getRadians());
			balls[ballsShot].setActive(true);
			balls[ballsShot].setVisible(true);
			balls[ballsShot].setX(currentShotX);
			balls[ballsShot].setY(currentShotY);
			balls[ballsShot].setVelocity(cannonVector * cannonBallNS::SPEED);
			createParticleEffect(particleVector, particleSpeed, 50);
			ballsShot++;

 			reloadTimer = 0;
 			cannon.setFrames(0, 19);
			cannon.setCurrentFrame(0);
		}

		// update projectiles and goblins
		for(int i = 0; i < BALL_COUNT; i++){
			balls[i].update(frameTime);
			booms[i].update(frameTime);
		}

		for(int i = 0; i < GOBLIN_COUNT; i++){
			if (goblins[i].getActive()) {
				goblins[i].senseDistance(tower.getX() + (tower.getWidth() * TOWER_IMAGE_SCALE), level);
				goblins[i].update(frameTime);
			}
		}

		cannon.update(frameTime);

		if(cannon.getCurrentFrame() == 19) cannon.setFrames(19, 19);

		//particle update
		pm.update(frameTime);

		spawn = rand() % 150;

		goblinTimer += frameTime;
		if(spawn == 0 && goblinTimer >= MIN_GOBLIN_TIME && spawnCount < GOBLIN_COUNT){
			goblins[spawnCount].setX(GAME_WIDTH);
			goblins[spawnCount].setActive(true);
			goblins[spawnCount].setVisible(true);
			spawnCount += 1;
			goblinTimer = 0;
		}

		if(tower.getHealth() <= FULL_HEALTH * 0.2) tower.setTextureManager(&tower20Texture);
		else if(tower.getHealth() <= FULL_HEALTH * 0.4) tower.setTextureManager(&tower40Texture);
		else if(tower.getHealth() <= FULL_HEALTH * 0.6) tower.setTextureManager(&tower60Texture);
		else if(tower.getHealth() <= FULL_HEALTH * 0.8) tower.setTextureManager(&tower80Texture);
		else tower.setTextureManager(&tower100Texture);

		if(pointsToLose > 0 && negPointsTimer >= SCORE_POPUP_TIME) {
			score -= pointsToLose;
			pointsJustLost = pointsToLose;
			pointsToLose = 0;
			negPointsTimer = 0;
		}
		if(score < 0){
			score = 0;
		}
		negPointsTimer += frameTime;

		// NUKE
		if(input->isKeyDown(0x4E) && input->isKeyDown(0x55) && input->isKeyDown(0x4B) && input->isKeyDown(0x45)){
			nuke.setVisible(true);
			nuking = true;
		}

		if(nuking) {
			nuke.setY(nuke.getY() + 200 * frameTime);
			if(nuke.getY() + nuke.getHeight() * NUKE_IMAGE_SCALE > 600) {
				booms[0].setX(GAME_WIDTH / 2 - booms[0].getWidth() * NUKE_BOOM_IMAGE_SCALE / 2);
				booms[0].setY(0);
				booms[0].setActive(true);
				booms[0].setVisible(true);
				booms[0].setScale(NUKE_BOOM_IMAGE_SCALE);
				audio->playCue(BOOM);
			}
			if(nuke.getY() + nuke.getHeight() * NUKE_IMAGE_SCALE > 800) {
				for(int i = 0; i < GOBLIN_COUNT; i++) {
					goblins[i].setActive(false);
 					goblins[i].setVisible(false);
					audio->playCue(GROWL);
					killCount++;
					audio->playCue(BOOM);
				}
				nuking = false;
				nuke.setX(GAME_WIDTH / 2 - nuke.getWidth() * NUKE_IMAGE_SCALE / 2);
				nuke.setY(-nuke.getHeight() * NUKE_IMAGE_SCALE);
				booms[0].setActive(false);
				booms[0].setVisible(false);
				booms[0].setScale(BOOM_IMAGE_SCALE);
			}
		}

		
	
		break;

	case bossFight:
		//aim cannon 
		if(input->isKeyDown(VK_UP)){
			if(cannon.getRadians() > -1){
				cannon.setRadians(cannon.getRadians() - ROATATION_SPEED);
			}

		}
		else if(input->isKeyDown(VK_DOWN)){
			if(cannon.getRadians() < 1){
				cannon.setRadians(cannon.getRadians() + ROATATION_SPEED);
			}
		}

		for(int i = 0; i < RELOADING_IMAGE_COUNT; i++) {
			reloading[i].setRadians(cannon.getRadians());
			// 
			reloading[i].setY(RELOADING_IMAGE_STARTING_Y - (45 - i) * sin(cannon.getRadians()));
			reloading[i].setX(RELOADING_IMAGE_STARTING_X + RELOADING_IMAGE_COUNT - (45 - i) * cos(cannon.getRadians()));
		}

		currentShotX = cannon.getCenterX() + cannonRadius * cos(cannon.getRadians()) - (balls[0].getWidth()*BALL_IMAGE_SCALE)/2;
		currentShotY = cannon.getCenterY() + cannonRadius * sin(cannon.getRadians()) - (balls[0].getWidth()*BALL_IMAGE_SCALE)/2;

		cannonVector.x = cos(cannon.getRadians());
		cannonVector.y = -sin(cannon.getRadians()) * 1.25;

		// particle stuff
		particleVector.x = currentShotX + particleXOffset;
		particleVector.y = currentShotY + particleYOffset;
		particleSpeed = VECTOR2(cannonVector.x * 300,-cannonVector.y * 300);

		D3DXVec2Normalize(&cannonVector , &cannonVector);

		//shoot 
		if (ballsShot >= BALL_COUNT){
				ballsShot = 0;
		}
		reloadTimer += frameTime;
		if(input -> wasKeyPressed(VK_SPACE) && reloadTimer >= RELOAD_TIME && ballsShot < BALL_COUNT && balls[ballsShot].getActive() == false){

			//starting ball position
			currentShotX = cannon.getCenterX() + cannonRadius * cos(cannon.getRadians()) - (balls[0].getWidth()*BALL_IMAGE_SCALE)/2;
			currentShotY = cannon.getCenterY() + cannonRadius * sin(cannon.getRadians()) - (balls[0].getWidth()*BALL_IMAGE_SCALE)/2;
			//angle of the shot
			cannonVector.x = cos(cannon.getRadians());
			cannonVector.y = sin(cannon.getRadians()) * 1.25;
			D3DXVec2Normalize(&cannonVector , &cannonVector);

			// particle stuff
			particleVector.x = currentShotX + particleXOffset;
			particleVector.y = currentShotY + particleYOffset;
			particleSpeed = VECTOR2(cannonVector.x * 300, cannonVector.y * 300);

			audio->playCue(FIRE); 
			pm.rotateImage(cannon.getRadians());
			balls[ballsShot].setActive(true);
			balls[ballsShot].setVisible(true);
			balls[ballsShot].setX(currentShotX);
			balls[ballsShot].setY(currentShotY);
			balls[ballsShot].setVelocity(cannonVector * cannonBallNS::SPEED);
			createParticleEffect(particleVector, particleSpeed, 50);
			ballsShot++;

 			reloadTimer = 0;
 			cannon.setFrames(0, 19);
			cannon.setCurrentFrame(0);
		}	

		// update projectiles and goblins
		for(int i = 0; i < BALL_COUNT; i++){
			balls[i].update(frameTime);
			booms[i].update(frameTime);
		}
		
		if(boss.getHealth() > 0){
			boss.setActive(true);
			boss.setVisible(true);
		}
		if(boss.getHealth() <= 0){
			boss.setActive(false);
			boss.setVisible(false);
		}
		boss.update(frameTime);

		cannon.update(frameTime);
		if(cannon.getCurrentFrame() == 19) cannon.setFrames(19, 19);

		if(boss.getX() < 330){
			boss.setVelocity(VECTOR2(0,0));
			boss.setFrames(goblinNS::ATTACK_START_FRAME, goblinNS::ATTACK_END_FRAME);
		}

		//particle update
		pm.update(frameTime);

	
		if(tower.getHealth() <= FULL_HEALTH * 0.2) tower.setTextureManager(&tower20Texture);
		else if(tower.getHealth() <= FULL_HEALTH * 0.4) tower.setTextureManager(&tower40Texture);
		else if(tower.getHealth() <= FULL_HEALTH * 0.6) tower.setTextureManager(&tower60Texture);
		else if(tower.getHealth() <= FULL_HEALTH * 0.8) tower.setTextureManager(&tower80Texture);
		else tower.setTextureManager(&tower100Texture);

		if(pointsToLose > 0 && negPointsTimer >= SCORE_POPUP_TIME) {
			score -= pointsToLose;
			pointsJustLost = pointsToLose;
			pointsToLose = 0;
			negPointsTimer = 0;
		}
		if(score < 0){
			score = 0;
		}
		negPointsTimer += frameTime;

		break;
	case store:

		storeMenu -> update();
		ballsShot = 0;
		switch (storeMenu->getSelectedItem()) {

		case 0:
			if(score >= PRICE) {
				score -= PRICE;
				RELOAD_TIME -= RELOAD_UPGRADE;
				cannon.setFrameDelay(RELOAD_TIME/20);
				upgrade1++;
			}
			break;
	
		case 1:
			if(score >= PRICE) {
				score -= PRICE;
				FULL_HEALTH += 10;
				tower.setHealth(FULL_HEALTH);
				upgrade2++;
			}
			break;
	
		case 2:
			if(score >= PRICE) {
				score -= PRICE;
				for(int i = 0; i < BALL_COUNT; i++) booms[i].setBoomRadiusOffset(booms[i].getBoomRadiusOffset() - 10);
				for(int i = 0; i < BALL_COUNT; i++){
					booms[i].setScale(booms[i].getScale() +.015);
				}
				upgrade3++;
				boomOffSetX -= 4;
				boomOffSetY -= 4;
			}
			break;

		}

		currentMenu = -1;
		
		if(input->wasKeyPressed(VK_ESCAPE)) {
			tower.setHealth(FULL_HEALTH); // late because we don't want it in resetGame. I forget why.
			gameStates = gamePlay;
		}
		
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
		// not technically a collision, but remove castle health once per goblin attack loop
		if(goblins[i].getActive() && goblins[i].getX() < GAME_WIDTH && goblins[i].getCurrentFrame() == 64) {
			if (!goblins[i].wasAttackedThisLoop()) {
 				tower.setHealth(tower.getHealth() - 5);
				pointsToLose += 10;
				goblins[i].setAttackedThisLoop(true);
			}
		}
		else goblins[i].setAttackedThisLoop(false);
	}

	for(int i = 0; i < GOBLIN_COUNT; i++){
		// not technically a collision, but remove castle health once per goblin attack loop
		if(boss.getActive() && boss.getX() < GAME_WIDTH && boss.getCurrentFrame() == 64) {
			if (!boss.wasAttackedThisLoop()) {
 				tower.setHealth(tower.getHealth() - 20);
				pointsToLose += 50;
				boss.setAttackedThisLoop(true);
			}
		}
		else boss.setAttackedThisLoop(false);
	}

	if(gameStates == gamePlay){
		for(int i = 0; i < BALL_COUNT; i++){
			for(int j = 0; j < GOBLIN_COUNT; j++){
 				if(balls[i].collidesWith(goblins[j], collisionVector)){
 					goblins[j].setActive(false);
 					goblins[j].setVisible(false);
					audio->playCue(GROWL);
					killCount++;
					scorePopups[j].x = goblins[j].getX();
					scorePopups[j].timer = frameTime;
					score += goblins[j].getX() / SCORE_DIVIDER;
				}
			}
		}

		// boom collisions for area damage
		for(int i = 0; i < BALL_COUNT; i++){
 			for(int j = 0; j < GOBLIN_COUNT; j++){
				if(booms[i].timeOnScreen < BOOM_TIME / 2 && booms[i].collidesWith(goblins[j], collisionVector)){
      				goblins[j].setActive(false);
 					goblins[j].setVisible(false);
					audio->playCue(GROWL);
					killCount++;
					scorePopups[j].x = goblins[j].getX();
					scorePopups[j].timer = frameTime;
					score += goblins[j].getX() / SCORE_DIVIDER;
				}
			}
			if(balls[i].getY() + balls[i].getHeight() * BALL_IMAGE_SCALE >= 610 && balls[i].getActive()){
				audio->playCue(BOOM);
				displayBoom(balls[i].getX() - 30, balls[i].getY() - 40);
				balls[i].setActive(false);
				balls[i].setVisible(false);
			}
		}
	}
	if(gameStates == bossFight){
		for(int i = 0; i < BALL_COUNT; i++){
			if(balls[i].collidesWith(boss, collisionVector)){
				audio->playCue(BOOM);
				scorePopups[0].x = boss.getX() + (boss.getWidth() * BOSS_IMAGE_SCALE) / 2;
				scorePopups[0].timer = frameTime;
				score += boss.getX() / SCORE_DIVIDER;
				displayBoom(balls[i].getX(), balls[i].getY());
				boss.setHealth(boss.getHealth() - 10);
				balls[i].setActive(false);
				balls[i].setVisible(false);
			} 
			if(balls[i].getY() + balls[i].getHeight() * BALL_IMAGE_SCALE >= 610 && balls[i].getActive()){
				audio->playCue(BOOM);
				displayBoom(balls[i].getX() - 30, balls[i].getY() - 40);
				balls[i].setActive(false);
				balls[i].setVisible(false);
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
			smallFont->print("Use up and down arrows to aim your gun.", 360, 150);
			smallFont->print("Click the space bar to shoot your gun.", 360, 200);
			smallFont->print("Keep goblins from reaching and destroying your castle.", 360, 250);
			smallFont->print("Earn money by killing goblins.", 360, 300);
			smallFont->print("Kill goblins farther away from the castle for more money.", 360, 350);
			smallFont->print("Spend the least money and win for the highest score.", 360, 400);
			highlightFont->print("Press ESC to Return to Main Menu", 360, 480);
		}
		else if (currentMenu == 2) {
			headingFont->print("Credits:", 360, 50);
			smallFont -> setFontColor(graphicsNS::RED);
			smallFont->print("Designers/Coders/Artists/All Around Good Kids", 360, 200);
			smallFont -> setFontColor(graphicsNS::WHITE);
			smallFont->print("Dan Brown", 360, 250);
			smallFont->print("Tyler Mulley", 360, 300);
			highlightFont->print("Press ESC to Return to Main Menu", 360, 480);	
		}
		break;
	case gamePlay:
		tower.draw();
		smallFont->print("Level: "  + std::to_string(level), 1200, 10);
		pole.draw();
		backTower.draw();
		cannon.draw();
		
		for(int i = 0; i < GOBLIN_COUNT; i++){
			goblins[i].draw();

			if(scorePopups[i].timer > 0 && scorePopups[i].timer < SCORE_POPUP_TIME) {
				scorePopupFont->print("$" + std::to_string(scorePopups[i].x / SCORE_DIVIDER), scorePopups[i].x + 20, 500 - scorePopups[i].timer * 100);
				scorePopups[i].timer += frameTime;
			}
		}

		if(negPointsTimer < SCORE_POPUP_TIME) negPointsFont->print("-$" + std::to_string(pointsJustLost), 410, 500 - negPointsTimer * 100);
		
		nuke.draw();
		for(int i = 0; i < BALL_COUNT; i++){
			balls[i].draw();
			booms[i].draw();
		}
		pm.draw();

		smallFont->setFontColor(graphicsNS::GREEN);
		smallFont->print("$" + std::to_string(score), 10, 10);
		smallFont->setFontColor(graphicsNS::WHITE);

		break;
	case inBetween:
		if (inBetweenCount == 0) headingFont->print("Level " + std::to_string(level), 550, 275);
		if (inBetweenCount == 1) headingFont->print("Level " + std::to_string(level) + " Cleared", 450, 275);
		if (inBetweenCount == 2) headingFont->print("Level " + std::to_string(level), 550, 275);
		if (inBetweenCount == 3) headingFont->print("Level " + std::to_string(level) + " Cleared", 450, 275);
		if (inBetweenCount == 4) headingFont->print("Level " + std::to_string(level), 550, 275);
		if (inBetweenCount == 5) headingFont->print("Level " + std::to_string(level) + " Cleared", 450, 275);
		if (inBetweenCount == 6) headingFont->print("Boss Level", 550, 275);
		if (inBetweenCount == 7) headingFont->print("Boss Level Cleared", 450, 275);
		
		timeInBetween += frameTime;
		break;
	case store:
		storeMenu->displayMenu();
		resetGame();
		smallFont->setFontColor(graphicsNS::GREEN);
		smallFont->print("$" + std::to_string(score), 10, 10);
		smallFont->setFontColor(graphicsNS::WHITE);
		highlightFont->print("Press ENTER to buy, ESCAPE to continue.", 230, 485);
		smallFont->print("[ " + std::to_string(upgrade1) + " ]", 1050, 190);
		smallFont->print("[ " + std::to_string(upgrade2) + " ]", 1050, 280);
		smallFont->print("[ " + std::to_string(upgrade3) + " ]", 1050, 370);

		break;
	case bossFight:
		tower.draw();
		smallFont->print("Level: BOSS", 1150, 10);
		pole.draw();
		backTower.draw();
		cannon.draw();
		boss.draw();

		if(scorePopups[0].timer > 0 && scorePopups[0].timer < SCORE_POPUP_TIME) {
			scorePopupFont->print("$" + std::to_string(scorePopups[0].x / SCORE_DIVIDER), scorePopups[0].x + 20, 200 - scorePopups[0].timer * 100);
			scorePopups[0].timer += frameTime;
		}
		if(negPointsTimer < SCORE_POPUP_TIME) negPointsFont->print("-$" + std::to_string(pointsJustLost), 410, 500 - negPointsTimer * 100);
		
		nuke.draw();
		for(int i = 0; i < BALL_COUNT; i++){
			balls[i].draw();
			booms[i].draw();
		}
		pm.draw();

		smallFont->setFontColor(graphicsNS::GREEN);
		smallFont->print("$" + std::to_string(score), 10, 10);
		smallFont->setFontColor(graphicsNS::WHITE);

		
		break;
	case end:
		if (lastMenu->getSelectedItem() < 0) lastMenu -> displayMenu();
		else if (lastMenu->getSelectedItem() == 0){
			resetGame();
			gameStates = gamePlay;
			score = 0;  // reset this late so we can show score on end screen
			tower.setHealth(FULL_HEALTH); // same ^^
			RELOAD_TIME = 1.4; // same
			FULL_HEALTH = 100; // same
			currentMenu = -1;
		}
		else if (lastMenu->getSelectedItem() == 1) {
			PostQuitMessage(0);
		}

		if(tower.getHealth() <= 0) headingFont->print("You Died", 560, 450);
		else headingFont->print("Score: " + std::to_string(score), 525, 450);
		
		break;
	}

	if(splashTimer < 3) {
		//splash.draw();
		splashTimer += frameTime;
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

void Spacewar::displayBoom(int x, int y){
	booms[boomsUsed].setX(x + boomOffSetX - 10);
	booms[boomsUsed].setY(y + boomOffSetY - 20);
	booms[boomsUsed].setActive(true);
	booms[boomsUsed].setVisible(true);
	boomsUsed++;
 	if (boomsUsed == BALL_COUNT) boomsUsed = 0;

}

void Spacewar::resetGame() {

	for(int i = 0; i < GOBLIN_COUNT; i++) {
		goblins[i].setFrames(goblinNS::WALK_START_FRAME, goblinNS::WALK_END_FRAME);
		goblins[i].setCurrentFrame(goblinNS::WALK_START_FRAME);
		goblins[i].setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY);

		goblins[i].setVisible(false);
		goblins[i].setActive(false);

		scorePopups[i].timer = SCORE_POPUP_TIME;
	}

	for(int i = 0; i < BALL_COUNT; i++) {
		booms[i].setVisible(false);
		booms[i].setActive(false);
	
		balls[i].setVisible(false);
		balls[i].setActive(false);
	}

	reloadTimer = RELOAD_TIME;
	pointsToLose = 0;
	pointsJustLost = 0;

	spawnCount = 0;
	killCount = 0;
	cannon.setDegrees(0);

	negPointsTimer = SCORE_POPUP_TIME;
}
