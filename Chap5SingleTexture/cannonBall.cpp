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
	velocity.x = cannonBallNS::SPEED;                           // velocity X 
	velocity.y = -cannonBallNS::SPEED;
	active = false;
	firstShot = true;
}

void cannonBall::update(float frameTime){
	Entity::update(frameTime);
	
}

void cannonBall::setBallMovement(D3DXVECTOR3 vec, float frameTime){
  	if(active){
		
		if(firstShot){
			velocity.x = velocity.x * vec.x;
			velocity.y = velocity.y * vec.y;
			firstShot = false;
		}

		// number is gravity
		velocity.y = (velocity.y + (800 * frameTime));

		spriteData.x += velocity.x * frameTime;
		spriteData.y += velocity.y * frameTime;
	}

}
