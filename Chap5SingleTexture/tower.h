// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 planet.h v1.0

#ifndef _TOWER_H               // Prevent multiple definitions if this 
#define _TOWER_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"


namespace towerNS
{
    const int   WIDTH = 156;                // image width
    const int   HEIGHT = 174;               // image height
    const int   COLLISION_RADIUS = 156/2;   // for circular collision
    const int   X = 225; // location on screen
    const int   Y = 333;
}

class Tower : public Entity            // inherits from Entity class
{
public:
    // constructor
    Tower();
	void update(float frameTime);
	float getHealth(){ return health; }
	void setHealth(float h){ health = h; }

private:
	float health;
};
#endif