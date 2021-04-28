//I really should have made this a object to be inherited. I wish i could have a little more time to restructure the code.

#pragma once

#include <vector>
#include <map>

#include "Object.h"
#include "FishObject.h"
#include "DialogObject.h"
#include "objectManager.h"

class MenuObject :
	public CObject,
	public CSettings
{
public:
	MenuObject(Vector3 v);

	CSpriteDesc3D* selectedFishingPole = nullptr;
	CSpriteDesc3D* selectedBoat = nullptr; //can be null
	CSpriteDesc3D* selectedWeight = nullptr; //can be null
	CSpriteDesc3D* selectedLure = nullptr; //(bait) not priority. can be null

	bool addFish(CObject* fishy); //sets the vector of the fish relative to the menu

	void move(); //will only move the menu
	void resetMenuBackground(); // makes all highlights and selections normal.

	void sendMouseHover(POINT p);
	void sendMouseClick(POINT p);
	
	bool toggleMenu(POINT p);
	bool toggleMenu(eSpriteType t);

	bool isDialogOpen = false;

	void setInventoryPositions(); //this sets the position of all items in the menuFishList.
	void setGearPositions(); //sets the position of all items in the gear tab.
	list<CSpriteDesc3D*> getDisplayList();
	list<CSpriteDesc3D*> getSelectedGear();

	CObject* getDialogBox();
private:

	struct gearItems {
		CSpriteDesc3D* sprite;
		bool hasPurchased;
	};

	void handleInventoryHover(POINT p);
	void handleInventoryClick(POINT p);

	void handleGearHover(POINT p);
	void handleGearClick(POINT p);

	bool menuOpen;
	bool isFullyClosed = true; //we check this variable so we dont waste resources drawing hidden items in the menu.

	DialogObject* dialogBox = nullptr;

	list<CObject*> menuFishList;
	list<CObject*> selectedFish;

	
	vector<gearItems> boatList; //the boolean is to check if it was purchased and can be selected.
	vector<gearItems> weightList;
	vector<gearItems> poleList;
	vector<gearItems> lureList;

	

	bool highlightedBoat, highlightedWeight, highlightedFishingPole;
	CSpriteDesc3D* highlightedSprite = nullptr;

	vector<CSpriteDesc3D*> backgroundList; //this holds the colour of the background for each individual inventory slot.
	vector<CSpriteDesc3D*> gearBackgroundList;
	vector<CSpriteDesc3D*> gearLocks;

	list<CSpriteDesc3D*> displayList;
	list<CSpriteDesc3D*> gearDisplayList;
	vector<Vector3> inventoryPositions;
	vector<Vector3> gearPositions;

	//list<CObject> weightList -- chose different sinks so that the hook can sink faster and slower, while adding and losing control respectively
	//list<CObject*> baitList;
	CObject* parent1 = nullptr;
	CObject* parent2 = nullptr;

	int numFish = 0;
	int maxFish = 21;
	int maxList = 21;
};
