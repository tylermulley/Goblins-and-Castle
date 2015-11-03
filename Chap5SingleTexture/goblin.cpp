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
	velocity.x = goblinNS::SPEED;                           // velocity X 
	velocity.y = 0;
	active = false;
	atTower = false;
}

void Goblin::update(float frameTime){
	Entity::update(frameTime);
	if(!active || atTower) return;

	spriteData.x -= velocity.x * frameTime;

	
	
}

