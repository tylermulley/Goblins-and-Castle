
#include "endMenu.h"

endMenu::endMenu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
}

void endMenu::initialize(Graphics *g, Input *i)
{
	menuHeading ="GAME OVER";
	menuItem1 = "Play Again";
	menuItem2 = "Credits";
	menuItem3 = "Quit";
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
}

void endMenu::update()
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
			linePtr--;
		}
	}
	if(!downDepressedLastFrame){
		if (input->wasKeyPressed(VK_DOWN))
		{
			downDepressedLastFrame = true;
			linePtr++;
		}
	}
	if (linePtr > 2) linePtr = 0;
	if (linePtr < 0) linePtr = 2;

	if (input->isKeyDown(VK_RETURN))
		selectedItem = linePtr;
	else selectedItem = -1;
}

void endMenu::displayMenu()
{
	menuHeadingFont->print(menuHeading, menuAnchor.x, menuAnchor.y);
	int foo = 2*verticalOffset;

	if (linePtr==0)
		menuItemFontHighlight->print(menuItem1, itemsMid, menuAnchor.y + foo);
	else
		menuItemFont->print(menuItem1, itemsMid, menuAnchor.y+foo);
	foo = 3*verticalOffset;
	if (linePtr==1)
		menuItemFontHighlight->print(menuItem2, itemsMid, menuAnchor.y+foo);
	else
		menuItemFont->print(menuItem2, itemsMid, menuAnchor.y+foo);
	foo = 4*verticalOffset;

	if (linePtr==2)
		menuItemFontHighlight->print(menuItem3, itemsMid, menuAnchor.y+foo);
	else
		menuItemFont->print(menuItem3, itemsMid, menuAnchor.y+foo);
}
