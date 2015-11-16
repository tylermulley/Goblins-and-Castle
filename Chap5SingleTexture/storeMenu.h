
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef STOREMENU_H                 // Prevent multiple definitions if this 
#define STOREMENU_H 

class StoreMenu;

#include "graphics.h"
#include "constants.h"
#include "textDX.h"
#include <string>
#include <sstream>
#include "input.h"
#include "entity.h"

namespace StoreMenuNS
{ }

// inherits from Entity class
class StoreMenu : Entity
{
private:
   TextDX *menuItemFont;
   TextDX *menuItemFontHighlight;
   TextDX *menuHeadingFont;
   Input   *input;         // pointer to the input system
   Graphics *graphics;
   int selectedItem;
   std::string menuHeading;
   std::string menuItem1;
   std::string menuItem2;
   std::string menuItem3;
   std::string menuItem4;
   D3DXVECTOR2 menuAnchor;
   int itemsMid;
   int verticalOffset;
   int linePtr;
   COLOR_ARGB highlightColor ;
   COLOR_ARGB normalColor;
   bool upDepressedLastFrame;
   bool downDepressedLastFrame;
  

public:
    // constructor
    StoreMenu();
	void initialize(Game *gamePtr, Graphics *g, Input *i);
	void update();
	int getSelectedItem() {return selectedItem;}
	void setSelectedItem(int s) {selectedItem = s;}
	void displayMenu();
	
};
#endif

