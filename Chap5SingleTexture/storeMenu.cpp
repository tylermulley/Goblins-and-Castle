
#include "storeMenu.h"

StoreMenu::StoreMenu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
}

void StoreMenu::initialize(Game *gamePtr, Graphics *g, Input *i)
{
	menuHeading = "Upgrades $" + std::to_string(PRICE) + " Each";
	menuItem1 = "Increase Fire Rate";
	menuItem2 = "Increase Tower Armor";
	menuItem3 = "Increase Explosion Radius";

	highlightColor = graphicsNS::RED;
	normalColor = graphicsNS::WHITE;

	menuAnchor = D3DXVECTOR2(400,10);
	itemsMid = 580;
	input = i;
	verticalOffset = 90;
	linePtr = 0;
	selectedItem = -1;
	graphics = g;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	if(menuItemFont->initialize(graphics, 50, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 70, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 100, true, false, "Calibri") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));
	menuHeadingFont->setFontColor(normalColor);
	menuItemFont->setFontColor(normalColor);
	menuItemFontHighlight->setFontColor(highlightColor);

	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
	returnDepressedLastFrame = false;

	audio = gamePtr->getAudio();
}

void StoreMenu::update()
{
	selectedItem = -1;

	if(!(input->isKeyDown(VK_UP))){
		upDepressedLastFrame = false;
	}
	if(!(input->isKeyDown(VK_DOWN))){
		downDepressedLastFrame = false;
	}
	if(!(input->isKeyDown(VK_RETURN))){
		returnDepressedLastFrame = false;
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

	if(!returnDepressedLastFrame) {
		if (input->isKeyDown(VK_RETURN)) {
			returnDepressedLastFrame = true;
			audio->playCue(BEEP);
			selectedItem = linePtr;
		}
	}
	else selectedItem = -1;
}

void StoreMenu::displayMenu()
{
	menuHeadingFont->print(menuHeading, menuAnchor.x - 50, menuAnchor.y);
	int foo = 2*verticalOffset;

	if (linePtr==0)
		menuItemFontHighlight->print(menuItem1, itemsMid - 130, menuAnchor.y + foo);
	else
		menuItemFont->print(menuItem1, itemsMid - 130, menuAnchor.y+foo);
	foo = 3*verticalOffset;
	if (linePtr==1)
		menuItemFontHighlight->print(menuItem2, itemsMid - 130, menuAnchor.y+foo);
	else
		menuItemFont->print(menuItem2, itemsMid - 130, menuAnchor.y+foo);
	foo = 4*verticalOffset;

	if (linePtr==2)
		menuItemFontHighlight->print(menuItem3, itemsMid - 130, menuAnchor.y+foo);
	else
		menuItemFont->print(menuItem3, itemsMid - 130, menuAnchor.y+foo);
}

