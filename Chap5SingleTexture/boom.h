// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 planet.h v1.0

#ifndef _BOOM_H               // Prevent multiple definitions if this 
#define _BOOM_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"


namespace boomNS
{
    const int   WIDTH = 512;                // image width
    const int   HEIGHT = 512;               // image height
    const int   COLLISION_RADIUS = 512/2;   // for circular collision
    const int   X = GAME_WIDTH/2 - WIDTH/2; // location on screen
    const int   Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float MASS = 1.0e14f;         // mass
	const float SPEED = 0;	
    const int   TEXTURE_COLS = 3;       // texture has 2 columns
    const int   START_FRAME = 0;        // starts at frame 1
    const int   END_FRAME = 2;     
	const float BOOM_ANIMATION_DELAY = .1f;
	
}

class Boom : public Entity            // inherits from Entity class
{
public:
    // constructor
    Boom();
	void update(float frameTime);
	float timeOnScreen;
	int getBoomRadiusOffset() { return BOOM_RADIUS_OFFSET; }
	void setBoomRadiusOffset(int os) { BOOM_RADIUS_OFFSET = os; }
private:
	int BOOM_RADIUS_OFFSET;
};
#endif