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
	spriteData.rect.bottom = goblinNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = goblinNS::WIDTH;
    radius          = goblinNS::COLLISION_RADIUS;
    mass            = goblinNS::MASS;
	velocity.x = -goblinNS::SPEED;                           // velocity X 
	velocity.y = 0;
	active = false;
	atTower = false;
}

void Goblin::update(float frameTime){
	Entity::update(frameTime);
	if(!atTower) spriteData.x += velocity.x * frameTime;

	
	
}

int Goblin::getDistance(int currentCastleWidth) {
	return getX() - currentCastleWidth;
}

/*
void Goblin::senseDistance(int wallX){
	float distance = spriteData.x - wallX;
	float maxDistance = GAME_WIDTH - wallX;

	// change speed based on distance from wall and framedelay
	// if at tower do not execute large if else if
	if(!atTower){
		if(distance/maxDistance < .1) {
			velocity.x = goblinNS::SPEED + 45;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_9);
		}
		else if(distance/maxDistance < .2) {
			velocity.x = goblinNS::SPEED + 40;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_8);
		}
		else if(distance/maxDistance < .3) {
			velocity.x = goblinNS::SPEED + 35;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_7);
		}
		else if(distance/maxDistance < .4) {
			velocity.x = goblinNS::SPEED + 30;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_6);
		}
		else if(distance/maxDistance < .5){
			velocity.x = goblinNS::SPEED + 25;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_5);
		}
		else if(distance/maxDistance < .6) {
			velocity.x = goblinNS::SPEED + 20;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_4);
		}
		else if(distance/maxDistance < .7) {
			velocity.x = goblinNS::SPEED + 15;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_3);
		}
		else if(distance/maxDistance < .8) {
			velocity.x = goblinNS::SPEED + 10;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_2);
		}
		else if(distance/maxDistance < .9){
			velocity.x = goblinNS::SPEED + 5;
			setFrameDelay(goblinNS::GOBLIN_ANIMATION_DELAY_1);
		}
	}
	
	
}
*/

