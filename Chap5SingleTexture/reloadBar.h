// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 planet.h v1.0

#ifndef _RELOADBAR_H               // Prevent multiple definitions if this 
#define _RELOADBAR_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"


namespace reloadBarNS
{
    const int   WIDTH = 100;                // image width
    const int   HEIGHT = 80;               // image height
    const int   TEXTURE_COLS = 10;       // texture has 2 columns
    const int   START_FRAME = 0;        // starts at frame 1
    const int   END_FRAME = 9;          // no animation
	//const float ANIMATION_DELAY = 0.09f;
}

class ReloadBar : public Entity            // inherits from Entity class
{
public:
    // constructor
    ReloadBar();
	void update(float frameTime);
	
};
#endif