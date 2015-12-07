// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "goblin.h"
#include "math.h"

//=============================================================================
// default constructor
//=============================================================================
Goblin::Goblin() : Entity()
{
    spriteData.x    = goblinNS::X;              // location on screen
    spriteData.y    = goblinNS::Y;
	spriteData.width = goblinNS::WIDTH;           // size of boat1
    spriteData.height = goblinNS::HEIGHT;
    radius          = goblinNS::COLLISION_RADIUS;
    mass            = goblinNS::MASS;
	velocity.x = -goblinNS::SPEED;                           // velocity X 
	velocity.y = 0;
	active = false;  
	collisionType = entityNS::BOX;
	attackedThisLoop = false;
	isBoss = false;
}

void Goblin::update(float frameTime){
	Entity::update(frameTime);
	spriteData.x += velocity.x * frameTime;

	// confusing but leave them
	if (isBoss){
		edge.bottom = spriteData.y + (spriteData.height * BOSS_IMAGE_SCALE) - 19;
		edge.top = spriteData.y + 19;
		edge.right = spriteData.x + (spriteData.width * BOSS_IMAGE_SCALE) - (spriteData.width * BOSS_IMAGE_SCALE) / 2 - 5;
		edge.left = spriteData.x + (spriteData.width * BOSS_IMAGE_SCALE) / 2 + 5;	
	}
	else{
		edge.bottom = spriteData.y + (spriteData.height * GOBLIN_IMAGE_SCALE) - 19;
		edge.top = spriteData.y + 19;
		edge.right = spriteData.x + (spriteData.width * GOBLIN_IMAGE_SCALE) - (spriteData.width * GOBLIN_IMAGE_SCALE) / 2 - 5;
		edge.left = spriteData.x + (spriteData.width * GOBLIN_IMAGE_SCALE) / 2 + 5;	
	}
}

int Goblin::getDistance(int currentCastleWidth) {
	return getX() - currentCastleWidth;
}


void Goblin::senseDistance(int wallX, int level){
	// +50 lets it overlap castle a bit, for some depth
	float distance = spriteData.x + 50 - wallX;
	float maxDistance = GAME_WIDTH - wallX + 50;

	// change speed based on distance from wall and framedelay
	// if at tower do not execute large if else if
	if(distance > 0){
		if(distance/maxDistance < .1) {
			velocity.x = -goblinNS::SPEED - 45;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_9);
		}
		else if(distance/maxDistance < .2) {
			velocity.x = -goblinNS::SPEED - 40;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_8);
		}
		else if(distance/maxDistance < .3) {
			velocity.x = -goblinNS::SPEED - 35;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_7);
		}
		else if(distance/maxDistance < .4) {
			velocity.x = -goblinNS::SPEED - 30;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_6);
		}
		else if(distance/maxDistance < .5){
			velocity.x = -goblinNS::SPEED - 25;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_5);
		}
		else if(distance/maxDistance < .6) {
			velocity.x = -goblinNS::SPEED - 20;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_4);
		}
		else if(distance/maxDistance < .7) {
			velocity.x = -goblinNS::SPEED - 15;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_3);
		}
		else if(distance/maxDistance < .8) {
			velocity.x = -goblinNS::SPEED - 10;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_2);
		}
		else {
			velocity.x = -goblinNS::SPEED - 5;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_1);
		}
	}
	else {
		velocity.x = 0;
		setFrames(goblinNS::ATTACK_START_FRAME, goblinNS::ATTACK_END_FRAME);		
		setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY);
	}
	//velocity.x *= level * 0.85;
	velocity.x *= .85;
	setFrameDelay(getFrameDelay() / level);
}


