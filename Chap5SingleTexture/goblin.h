// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 planet.h v1.0

#ifndef _GOBLIN_H               // Prevent multiple definitions if this 
#define _GOBLIN_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"


namespace goblinNS
{
    const int   WIDTH = 65;                // image width
    const int   HEIGHT = 65;               // image height
    const int   COLLISION_RADIUS = 64/2.5;   // for circular collision
    const int   X = GAME_WIDTH; // location on screen
    const int   Y = 495;
    const float MASS = 1.0e14f;         // mass
	const float SPEED = 55;	
    const int   TEXTURE_COLS = 17;       // texture has 2 columns
    const int   WALK_START_FRAME = 57;        // starts at frame 1
    const int   WALK_END_FRAME = 51;          // no animation
	const int   ATTACK_START_FRAME = 61;        // starts at frame 1
    const int   ATTACK_END_FRAME = 67;          // no animation
	const float GOBLIN_ANIMATION_DELAY = 0.17f;
	const float GOBLIN_ANIMATION_DELAY_1 = 0.16f;
	const float GOBLIN_ANIMATION_DELAY_2 = 0.15f;
	const float GOBLIN_ANIMATION_DELAY_3 = 0.14f;
	const float GOBLIN_ANIMATION_DELAY_4 = 0.13f;
	const float GOBLIN_ANIMATION_DELAY_5 = 0.12f;
	const float GOBLIN_ANIMATION_DELAY_6 = 0.11f;
	const float GOBLIN_ANIMATION_DELAY_7 = 0.10f;
	const float GOBLIN_ANIMATION_DELAY_8 = 0.095f;
	const float GOBLIN_ANIMATION_DELAY_9 = 0.09f;
}

class Goblin : public Entity            // inherits from Entity class
{
public:
    // constructor
    Goblin();
	void update(float frameTime);
	void senseDistance(int wallX);

	bool atTower;
private:

	
};
#endif