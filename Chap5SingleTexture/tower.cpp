// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "tower.h"
#include "math.h"

//=============================================================================
// default constructor
//=============================================================================
Tower::Tower() : Entity()
{
    spriteData.x    = towerNS::X;              // location on screen
    spriteData.y    = towerNS::Y;
	spriteData.width = towerNS::WIDTH;           // size of boat1
    spriteData.height = towerNS::HEIGHT;
	spriteData.rect.bottom = towerNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = towerNS::WIDTH;
    radius          = towerNS::COLLISION_RADIUS;
	active = false;
	health = 100;
}

void Tower::update(float frameTime){
	Entity::update(frameTime);
}

