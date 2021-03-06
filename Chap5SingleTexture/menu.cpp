
#include "menu.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
}

void Menu::initialize(Game *gamePtr, Graphics *g, Input *i)
{
	menuHeading ="Bombin' Goblins";
	menuItem1 = "Play";
	menuItem2 = "Directions";
	menuItem3 = "Credits";

	highlightColor = graphicsNS::RED;
	normalColor = graphicsNS::WHITE;

	menuAnchor = D3DXVECTOR2(360,50);
	itemsMid = 580;
	input = i;
	verticalOffset = 100;
	linePtr = 0;
	selectedItem = -1;
	graphics = g;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	if(menuItemFont->initialize(graphics, 50, true, false, "Segoe Marker") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 70, true, false, "Segoe Marker") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 125, true, false, "Segoe Marker") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));
	menuHeadingFont->setFontColor(normalColor);
	menuItemFont->setFontColor(normalColor);
	menuItemFontHighlight->setFontColor(highlightColor);
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;

	audio = gamePtr->getAudio();
}

void Menu::update()
{
	if(!(input->isKeyDown(VK_UP))){
		upDepressedLastFrame = false;
	}
	if(!(input->isKeyDown(VK_DOWN))){
		downDepressedLastFrame = false;
	}

	if(!upDepressedLastFrame){
		if (input->wasKeyPressed(VK_UP))
		{
			upDepressedLastFrame = true;
			audio->playCue(BEEP);
			linePtr--;
		}
	}
	if(!downDepressedLastFrame){
		if (input->wasKeyPressed(VK_DOWN))
		{
			downDepressedLastFrame = true;
			audio->playCue(BEEP);
			linePtr++;
		}
	}
	if (linePtr > 2) linePtr = 0;
	if (linePtr < 0) linePtr = 2;

	if (input->isKeyDown(VK_RETURN)) {
		
		selectedItem = linePtr;
	}
	else selectedItem = -1;
}

void Menu::displayMenu()
{
	menuHeadingFont->print(menuHeading, menuAnchor.x, menuAnchor.y);
	int foo = 2*verticalOffset;

	if (linePtr==0)
		menuItemFontHighlight->print(menuItem1, itemsMid + 55, menuAnchor.y + foo - 10);
	else
		menuItemFont->print(menuItem1, itemsMid + 70, menuAnchor.y+foo);
	foo = 3*verticalOffset;
	if (linePtr==1)
		menuItemFontHighlight->print(menuItem2, itemsMid - 5, menuAnchor.y+foo - 10);
	else
		menuItemFont->print(menuItem2, itemsMid + 25, menuAnchor.y+foo);
	foo = 4*verticalOffset;

	if (linePtr==2)
		menuItemFontHighlight->print(menuItem3, itemsMid + 30, menuAnchor.y+foo - 10);
	else
		menuItemFont->print(menuItem3, itemsMid + 50, menuAnchor.y+foo);
}

