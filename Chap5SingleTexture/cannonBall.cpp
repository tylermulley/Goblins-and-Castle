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
	collisionType = entityNS::BOX;

}

void cannonBall::update(float frameTime){
	Entity::update(frameTime);
	
}

bool cannonBall::setBallMovement(D3DXVECTOR3 vec, float frameTime){
	Entity::update(frameTime);

	edge.bottom = spriteData.y + (spriteData.height * BALL_IMAGE_SCALE);
	edge.top = spriteData.y;
	edge.right = spriteData.x + (spriteData.width * BALL_IMAGE_SCALE);
	edge.left = spriteData.x;

	if(active){
		
		if(firstShot){
			velocity.x = velocity.x * vec.x;
			velocity.y = velocity.y * vec.y;
			firstShot = false;
		}

		// explicit number is gravity
		velocity.y = (velocity.y + (1000 * frameTime));

		if(spriteData.y + getHeight() * BALL_IMAGE_SCALE <= 610){
			spriteData.x += velocity.x * frameTime;
			spriteData.y += velocity.y * frameTime;
			
		}
		else{
			audio->playCue(BOOM);
			setActive(false);
			setVisible(false);
			
			firstShot = true;
			velocity.x = cannonBallNS::SPEED;                           // velocity X 
			velocity.y = -cannonBallNS::SPEED;
			return 1;
		}
		
	}
	return 0;

}
