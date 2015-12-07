// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "reloadBar.h"
#include "math.h"

//=============================================================================
// default constructor
//=============================================================================
ReloadBar::ReloadBar() : Entity()
{
	spriteData.width = reloadBarNS::WIDTH;           // size of boat1
    spriteData.height = reloadBarNS::HEIGHT;
	active = true;  
}

void ReloadBar::update(float frameTime){
	Entity::update(frameTime);

	if(getCurrentFrame() == 9){
		setFrames(reloadBarNS::END_FRAME, reloadBarNS::END_FRAME);
		setCurrentFrame(reloadBarNS::END_FRAME);
	}
	
	
}

