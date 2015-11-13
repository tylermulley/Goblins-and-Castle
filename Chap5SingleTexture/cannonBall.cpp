// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "cannonBall.h"
#include "math.h"

//=============================================================================
// default constructor
//=============================================================================
cannonBall::cannonBall() : Entity()
{
    spriteData.x    = cannonBallNS::X;              // location on screen
    spriteData.y    = cannonBallNS::Y;
	spriteData.width = cannonBallNS::WIDTH;           // size of boat1
    spriteData.height = cannonBallNS::HEIGHT;
	spriteData.rect.bottom = cannonBallNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = cannonBallNS::WIDTH;
    radius          = cannonBallNS::COLLISION_RADIUS;
    mass            = cannonBallNS::MASS;
	velocity.x = -cannonBallNS::SPEED;                           // velocity X 
	velocity.y = 0;
	active = false;
}

void cannonBall::update(float frameTime){
	Entity::update(frameTime);

	setActive(true);
	setVisible(true);
}



