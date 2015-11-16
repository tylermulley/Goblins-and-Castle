// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "boom.h"
#include "math.h"

//=============================================================================
// default constructor
//=============================================================================
Boom::Boom() : Entity()
{
    spriteData.x    = boomNS::X;              // location on screen
    spriteData.y    = boomNS::Y;
	spriteData.width = boomNS::WIDTH;           // size of boat1
    spriteData.height = boomNS::HEIGHT;
	spriteData.rect.bottom = boomNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = boomNS::WIDTH;
    radius          = boomNS::COLLISION_RADIUS;
    mass            = boomNS::MASS;
    velocity.x = 0;                           // velocity X 
	velocity.y = 0;
	timeOnScreen = 0;
	active = false;  
	collisionType = entityNS::BOX;
	BOOM_RADIUS_OFFSET = 15;
}

void Boom::update(float frameTime)
{
	Entity::update(frameTime);

	if(active) timeOnScreen += frameTime;

	if (timeOnScreen > BOOM_TIME){
		setActive(false);
		setVisible(false);
		setX(-2*GAME_WIDTH);
		setY(-2*GAME_HEIGHT);

		timeOnScreen = 0;
	}

	edge.bottom = spriteData.y + (spriteData.height * BOOM_IMAGE_SCALE) - BOOM_RADIUS_OFFSET;
	edge.top = spriteData.y + BOOM_RADIUS_OFFSET;
	edge.right = spriteData.x + (spriteData.width * BOOM_IMAGE_SCALE) - BOOM_RADIUS_OFFSET;
	edge.left = spriteData.x + BOOM_RADIUS_OFFSET;

}

