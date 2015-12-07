// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 planet.h v1.0

#ifndef _CANNONBALL_H               // Prevent multiple definitions if this 
#define _CANNONBALL_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"


namespace cannonBallNS
{
    const int   WIDTH = 250;                // image width
    const int   HEIGHT = 276;               // image height
	const int   COLLISION_RADIUS = (250/15);   // for circular collision
    const int   X = 300; // location on screen
    const int   Y = 300;
    const float MASS = 1.0e14f;         // mass
	const float SPEED = 800;	
    const int   TEXTURE_COLS = 2;       // texture has 2 columns
	const float BALL_ANIMATION_DELAY = 0.075f;
	const int   START_FRAME = 0;        // starts at frame 1
    const int   END_FRAME = 1;

}

class cannonBall : public Entity            // inherits from Entity class
{
public:
    // constructor
    cannonBall();
	void update(float frameTime);
	bool setBallMovement(D3DXVECTOR3 vec, float frameTime);
	bool firstShot;
	
private:

	
};
#endif