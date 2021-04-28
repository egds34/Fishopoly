#include "MenuObject.h"

MenuObject::MenuObject(Vector3 v) : CObject(INVENTORY_MENU, v)
{
	menuOpen = false;
	offset = 459;

	int currX = -33, currY = 151;
	//inventory
	for (int i = 0; i < maxList; ++i)
	{
		if ((i % 3 == 0) && (i != 0))
		{
			currX = -33;
			currY -= 46;
		}
		inventoryPositions.push_back(Vector3(currX, currY, 0));
		CSpriteDesc3D* p = new CSpriteDesc3D();
		p->m_nSpriteIndex = NORMAL_INVENTORY_BACKGROUND;
		backgroundList.push_back(p);
		currX += 48;
	}
	currX = -21; currY -= 35;
	for (int i = 0; i < 4; ++i)
	{
		if ((i % 2 == 0) && (i != 0))
		{	
			currX = -21;
			currY -= 22;
		}
		inventoryPositions.push_back(Vector3(currX, currY, 0));
		CSpriteDesc3D* p = new CSpriteDesc3D();
		switch (i)
		{
		case 0:
			p->m_nSpriteIndex = BUTTON_SELL_GRAY;
			break;
		case 1:
			p->m_nSpriteIndex = BUTTON_BREED_NORMAL;
			break;
		case 2:
			p->m_nSpriteIndex = BUTTON_INFO_GRAY;
			break;
		case 3:
			p->m_nSpriteIndex = BUTTON_RELEASE_GRAY;
			break;
		}		
		backgroundList.push_back(p);
		currX += 71;
	}
	setInventoryPositions();

	//gear
	currX = -33, currY = 151;
	for (int i = 0; i < 3; ++i)
	{
		gearPositions.push_back(Vector3(currX, currY, 0));
		CSpriteDesc3D* p = new CSpriteDesc3D();
		p->m_nSpriteIndex = NORMAL_ITEM_BACKGROUND;
		gearBackgroundList.push_back(p);
		currX += 48;
	}
	currX = -33, currY -= 66;
	for (int i = 0; i < 6; ++ i)
	{
		if ((i % 3 == 0) && (i != 0))
		{
			currX = -33;
			currY -= 46; //should be larger
		}
		gearPositions.push_back(Vector3(currX, currY, 0));
		CSpriteDesc3D* p = new CSpriteDesc3D();
		p->m_nSpriteIndex = NORMAL_ITEM_BACKGROUND;
		gearBackgroundList.push_back(p);
		currX += 48;
	}
	currX = -33, currY -= 66;
	for (int i = 0; i < 3; ++i)
	{
		gearPositions.push_back(Vector3(currX, currY, 0));
		CSpriteDesc3D* p = new CSpriteDesc3D();
		p->m_nSpriteIndex = NORMAL_ITEM_BACKGROUND;
		gearBackgroundList.push_back(p);
		currX += 48;
	}
	//currX = -33, currY -= 66; NO TIME FOR LURE
	//for (int i = 0; i < 6; ++i)
	//{
	//	if ((i % 3 == 0) && (i != 0))
	//	{
	//		currX = -33;
	//		currY -= 46; //should be larger
	//	}
	//	gearPositions.push_back(Vector3(currX, currY, 0));
	//	CSpriteDesc3D* p = new CSpriteDesc3D();
	//	p->m_nSpriteIndex = NORMAL_ITEM_BACKGROUND;
	//	gearBackgroundList.push_back(p);
	//	currX += 48;
	//}
	//currX = 15, currY -= 40;
	currX = -21, currY -= 152;
	gearPositions.push_back(Vector3(currX, currY, 0));
	CSpriteDesc3D* p = new CSpriteDesc3D();
	p->m_nSpriteIndex = BUTTON_SELECT_GRAY;
	gearBackgroundList.push_back(p);

	currX = 50, 
	gearPositions.push_back(Vector3(currX, currY, 0));
	CSpriteDesc3D* q = new CSpriteDesc3D();
	q->m_nSpriteIndex = BUTTON_BUY_GRAY;
	gearBackgroundList.push_back(q);

	selectedBoat = new CSpriteDesc3D();
	selectedBoat->m_nSpriteIndex = UNLOADED_FISH_SPRITE;
	selectedFishingPole = new CSpriteDesc3D();
	selectedFishingPole->m_nSpriteIndex = ICON_POLE_1;
	selectedWeight = new CSpriteDesc3D();
	selectedWeight->m_nSpriteIndex = UNLOADED_FISH_SPRITE;
	selectedBoat = new CSpriteDesc3D();
	selectedWeight->m_nSpriteIndex = UNLOADED_FISH_SPRITE;


	//different lists because only one can be selected at a time.

	for (int i = 0; i < 12; ++i)
	{
		CSpriteDesc3D* q = new CSpriteDesc3D();
		q->m_nSpriteIndex = ICON_LOCK;
		gearLocks.push_back(q);

		CSpriteDesc3D* p = new CSpriteDesc3D();
		gearItems item;
		switch (i)
		{
		case 0:
			p->m_nSpriteIndex = ICON_BOAT_1;
			item.hasPurchased = false;
			item.sprite = p;
			boatList.push_back(item);
			break;
		case 1:
			p->m_nSpriteIndex = ICON_BOAT_2;
			item.hasPurchased = false;
			item.sprite = p;
			boatList.push_back(item);;
			break;
		case 2:
			p->m_nSpriteIndex = ICON_BOAT_3;			
			item.hasPurchased = false;
			item.sprite = p;
			boatList.push_back(item);
			break;
		case 3:
			p->m_nSpriteIndex = ICON_WEIGHT_1;
			item.hasPurchased = false;
			item.sprite = p;
			weightList.push_back(item);
			break;
		case 4:
			p->m_nSpriteIndex = ICON_WEIGHT_2;
			item.hasPurchased = false;
			item.sprite = p;
			weightList.push_back(item);
			break;
		case 5:
			p->m_nSpriteIndex = ICON_WEIGHT_3;
			item.hasPurchased = false;
			item.sprite = p;
			weightList.push_back(item);
			break;
		case 6:
			p->m_nSpriteIndex = ICON_POLE_1;
			item.hasPurchased = true;
			item.sprite = p;
			poleList.push_back(item);
			break;
		case 7:
			p->m_nSpriteIndex = ICON_POLE_2;
			item.hasPurchased = false;
			item.sprite = p;
			poleList.push_back(item);
			break;
		case 8:
			p->m_nSpriteIndex = ICON_POLE_3;
			item.hasPurchased = false;
			item.sprite = p;
			poleList.push_back(item);
			break;
		case 9:
			p->m_nSpriteIndex = ICON_POLE_4;
			item.hasPurchased = false;
			item.sprite = p;
			poleList.push_back(item);
			break;
		case 10:
			p->m_nSpriteIndex = ICON_POLE_5;
			item.hasPurchased = false;
			item.sprite = p;
			poleList.push_back(item);
			break;
		case 11:
			p->m_nSpriteIndex = ICON_POLE_6;
			item.hasPurchased = false;
			item.sprite = p;
			poleList.push_back(item);
			break;
		}
	}
	setGearPositions();
}

bool MenuObject::addFish(CObject* fishy)
{
	if (numFish >= maxFish) return false;

	list<CObject*>::iterator iter = menuFishList.begin();
	for (int i = 0; i < numFish; ++i)
		++iter;

	fishy->m_fXScale = fishy->originalXScale * 0.5;
	fishy->m_fYScale = fishy->originalYScale * 0.5;
	menuFishList.insert(iter, fishy);
	++numFish;
	return true;
}

void MenuObject::move()
{

	offset += m_fSpeed * unit;
	if (offset >= 459.0f)
	{
		for (int i = 0; i < 12; ++i) //only one selection can be made at a time.
		{
			gearBackgroundList[i]->m_nSpriteIndex = NORMAL_ITEM_BACKGROUND;
		}
		highlightedSprite = nullptr;
		highlightedBoat = false;
		highlightedFishingPole = false;
		highlightedWeight = false;

		offset = 459.0;
		m_fSpeed = 0;
		isFullyClosed = true;
		resetMenuBackground();		
	}
	else if (offset <= 312.0f)
	{
		offset = 312.0f;
		m_fSpeed = 0;
		isFullyClosed = false;
	}

	if (PC->m_vPos.y < 0.0)
	{
		m_vPos.x = PC->m_vPos.x + offset;
		int index = 0;
		for (auto& i : menuFishList)
		{
			i->m_vPos = m_vPos + inventoryPositions[index];
			i->m_vPos.z -= 1;
			i->move();
			++index;
		}
		index = 0;
		for (auto& i : backgroundList)
		{
			i->m_vPos = m_vPos + inventoryPositions[index];
			i->m_vPos.y += 1;
			++index;
		}
		index = 0;
		for (auto& i : gearBackgroundList)
		{
			i->m_vPos = m_vPos + gearPositions[index];
			++index;
		}
		index = 0;
		for (auto& i : gearLocks)
		{
			i->m_vPos = m_vPos + gearPositions[index];
			i->m_vPos.z -= 1;
			++index;
		}
		index = 0;
		for (auto& i : boatList)
		{
			gearLocks[index]->m_vPos = i.sprite->m_vPos = m_vPos + gearPositions[index];
			if (i.hasPurchased == false) gearLocks[index]->m_vPos.z -= 1;
			else gearLocks[index]->m_vPos.z += 10;
			i.sprite->m_vPos.y += 1;
			++index;
		}
		for (auto& i : poleList)
		{
			gearLocks[index]->m_vPos = i.sprite->m_vPos = m_vPos + gearPositions[index];
			if (i.hasPurchased == false) gearLocks[index]->m_vPos.z -= 1;
			else gearLocks[index]->m_vPos.z += 10;
			i.sprite->m_vPos.y += 1;
			++index;
		}
		for (auto& i : weightList)
		{
			gearLocks[index]->m_vPos = i.sprite->m_vPos = m_vPos + gearPositions[index];
			if (i.hasPurchased == false) gearLocks[index]->m_vPos.z -= 1;
			else gearLocks[index]->m_vPos.z += 10;
			i.sprite->m_vPos.y += 1;
			++index;
		}
	}
	//needs to be set everytime becuase this is supposed to move with the penguin
	else
	{
		int index = 0;
		m_vPos = Vector3(PC->m_vPos.x + offset, PC->m_vPos.y + 26, 1000.0f);
		for (auto& i : menuFishList)
		{
			i->m_vPos = m_vPos + inventoryPositions[index];
			i->m_vPos.z -= 1;
			i->move();
			++index;
		}
		index = 0;
		for (auto& i : backgroundList)
		{
			i->m_vPos = m_vPos + inventoryPositions[index];
			i->m_vPos.y += 1;
			++index;
		}
		index = 0;
		for (auto& i : gearBackgroundList)
		{
			i->m_vPos = m_vPos + gearPositions[index];
			i->m_vPos.y += 1;
			++index;
		}
		index = 0;
		for (auto& i : boatList)
		{
			gearLocks[index]->m_vPos = i.sprite->m_vPos = m_vPos + gearPositions[index];
			if (i.hasPurchased == false) gearLocks[index]->m_vPos.z -= 1;
			else gearLocks[index]->m_vPos.z += 10;
			i.sprite->m_vPos.y += 1;
			++index;
		}
		for (auto& i : poleList)
		{
			gearLocks[index]->m_vPos = i.sprite->m_vPos = m_vPos + gearPositions[index];
			if (i.hasPurchased == false) gearLocks[index]->m_vPos.z -= 1;
			else gearLocks[index]->m_vPos.z += 10;
			i.sprite->m_vPos.y += 1;
			++index;
		}
		for (auto& i : weightList)
		{
			gearLocks[index]->m_vPos = i.sprite->m_vPos = m_vPos + gearPositions[index];
			if (i.hasPurchased == false) gearLocks[index]->m_vPos.z -= 1;
			else gearLocks[index]->m_vPos.z += 10;
			i.sprite->m_vPos.y += 1;
			++index;
		}
	}
}

void MenuObject::resetMenuBackground()
{
	for (auto& i : backgroundList)
	{
		if (i->m_nSpriteIndex <= NORMAL_INVENTORY_BACKGROUND) i->m_nSpriteIndex = NORMAL_INVENTORY_BACKGROUND;
		backgroundList[maxFish]->m_nSpriteIndex = BUTTON_SELL_GRAY;
		backgroundList[maxFish + 1]->m_nSpriteIndex = BUTTON_BREED_NORMAL;
		backgroundList[maxFish + 2]->m_nSpriteIndex = BUTTON_INFO_GRAY;
		backgroundList[maxFish + 3]->m_nSpriteIndex = BUTTON_RELEASE_GRAY;

		selectedFish.clear();
	}
}

void MenuObject::sendMouseHover(POINT p)
{
	switch (m_nSpriteIndex)
	{
	case INVENTORY_MENU:
		handleInventoryHover(p);
		break;
	case GEAR_MENU:
		handleGearHover(p);
		break;
	}
}

void MenuObject::sendMouseClick(POINT p)
{
	switch (m_nSpriteIndex)
	{
	case INVENTORY_MENU:
		handleInventoryClick(p);
		break;
	case GEAR_MENU:
		handleGearClick(p);
		break;
	}
}

void MenuObject::handleInventoryHover(POINT p)
{
	int x = ((p.x - (m_nWinWidth / 2)) * 0.625) + (int)PC->m_vPos.x;
	int y = 0.63 * ((m_nWinHeight - p.y) - 402);
	int index = 0;
	int highlightedIndex = -1;

	if (!isDialogOpen)
	{
		for (auto i : inventoryPositions)
		{
			if (index < maxFish)
			{
				if ((x > (PC->m_vPos.x + offset + i.x) - 24) && (x < (PC->m_vPos.x + offset + i.x) + 24))
				{
					if ((y > i.y - 22) && (y < i.y + 22)) highlightedIndex = index;
				}
			}
			else
			{
				if ((x > (PC->m_vPos.x + offset + i.x) - 36) && (x < (PC->m_vPos.x + offset + i.x) + 36))
				{
					if ((y > i.y - 11) && (y < i.y + 11)) highlightedIndex = index;
				}
			}

			if (backgroundList[index]->m_nSpriteIndex == HOVER_INVENTORY_BACKGROUND) backgroundList[index]->m_nSpriteIndex = NORMAL_INVENTORY_BACKGROUND;
			else if (backgroundList[index]->m_nSpriteIndex == SELECT_HOVER_INVENTORY_BACKGROUND) backgroundList[index]->m_nSpriteIndex = SELECT_INVENTORY_BACKGROUND;
			else if (backgroundList[index]->m_nSpriteIndex == BUTTON_SELL_HIGHLIGHTED) backgroundList[index]->m_nSpriteIndex = BUTTON_SELL_NORMAL;
			else if (backgroundList[index]->m_nSpriteIndex == BUTTON_INFO_HIGHLIGHTED) backgroundList[index]->m_nSpriteIndex = BUTTON_INFO_NORMAL;
			else if (backgroundList[index]->m_nSpriteIndex == BUTTON_BREED_HIGHLIGHTED) backgroundList[index]->m_nSpriteIndex = BUTTON_BREED_NORMAL;
			else if (backgroundList[index]->m_nSpriteIndex == BUTTON_RELEASE_HIGHLIGHTED) backgroundList[index]->m_nSpriteIndex = BUTTON_RELEASE_NORMAL;
			++index;
		}
		if (highlightedIndex >= 0)
		{
			if (backgroundList[highlightedIndex]->m_nSpriteIndex == NORMAL_INVENTORY_BACKGROUND) backgroundList[highlightedIndex]->m_nSpriteIndex = HOVER_INVENTORY_BACKGROUND;
			else if (backgroundList[highlightedIndex]->m_nSpriteIndex == SELECT_INVENTORY_BACKGROUND) backgroundList[highlightedIndex]->m_nSpriteIndex = SELECT_HOVER_INVENTORY_BACKGROUND;
			else if (backgroundList[highlightedIndex]->m_nSpriteIndex == BUTTON_SELL_NORMAL) backgroundList[highlightedIndex]->m_nSpriteIndex = BUTTON_SELL_HIGHLIGHTED;
			else if (backgroundList[highlightedIndex]->m_nSpriteIndex == BUTTON_INFO_NORMAL) backgroundList[highlightedIndex]->m_nSpriteIndex = BUTTON_INFO_HIGHLIGHTED;
			else if (backgroundList[highlightedIndex]->m_nSpriteIndex == BUTTON_BREED_NORMAL) backgroundList[highlightedIndex]->m_nSpriteIndex = BUTTON_BREED_HIGHLIGHTED;
			else if (backgroundList[highlightedIndex]->m_nSpriteIndex == BUTTON_RELEASE_NORMAL) backgroundList[highlightedIndex]->m_nSpriteIndex = BUTTON_RELEASE_HIGHLIGHTED;
		}
	}
	else dialogBox->handleMouseHover(p);
}

void MenuObject::handleInventoryClick(POINT p)
{
	int x = ((p.x - (m_nWinWidth / 2))  * 0.625) + (int)PC->m_vPos.x;
	int y = 0.63 * ((m_nWinHeight - p.y) - 402);
	int index = 0;

	if (!isDialogOpen)
	{
		for (auto i : inventoryPositions)
		{
			if (index < maxFish)
			{
				if ((x > (PC->m_vPos.x + offset + i.x) - 24) && (x < (PC->m_vPos.x + offset + i.x) + 24))
				{
					if ((y > i.y - 22) && (y < i.y + 22))
					{
						m_pAudio->play(SELECT);
						break;
					}
				}
			}
			else
			{
				if ((x > (PC->m_vPos.x + offset + i.x) - 36) && (x < (PC->m_vPos.x + offset + i.x) + 36))
				{
					if ((y > i.y - 11) && (y < i.y + 11))
					{
						m_pAudio->play(SELECT);
						break;
					}
				}
			}
			++index;

			//printf("%f %f\n", PC->m_vPos.x + offset + i.x,  i.y);
		}
		if (index < numFish) //we clicked an inventory with a fish in it
		{
			list<CObject*>::iterator iter = menuFishList.begin();
			if (backgroundList[index]->m_nSpriteIndex == HOVER_INVENTORY_BACKGROUND) //we added it to our selection
			{
				backgroundList[index]->m_nSpriteIndex = SELECT_HOVER_INVENTORY_BACKGROUND;
				advance(iter, index);
				selectedFish.push_back(*iter);
			}
			else if (backgroundList[index]->m_nSpriteIndex == SELECT_HOVER_INVENTORY_BACKGROUND) //we removed it from our selection
			{
				backgroundList[index]->m_nSpriteIndex = HOVER_INVENTORY_BACKGROUND;
				advance(iter, index);
				for (auto i = selectedFish.begin(); i != selectedFish.end();)
				{
					if (*iter == *i)
					{
						selectedFish.erase(i);
						break;
					}
					else ++i;
				}
			}

			//this is so that users cannot select invalid options for the fish they selected, this was poorly done. is that a deadline approaching?
			if (selectedFish.empty())
			{
				backgroundList[maxFish]->m_nSpriteIndex = BUTTON_SELL_GRAY;
				backgroundList[maxFish + 1]->m_nSpriteIndex = BUTTON_BREED_NORMAL;
				backgroundList[maxFish + 2]->m_nSpriteIndex = BUTTON_INFO_GRAY;
				backgroundList[maxFish + 3]->m_nSpriteIndex = BUTTON_RELEASE_GRAY;
			}
			else if (selectedFish.size() == 1)
			{
				backgroundList[maxFish]->m_nSpriteIndex = BUTTON_SELL_NORMAL;
				backgroundList[maxFish + 1]->m_nSpriteIndex = BUTTON_BREED_NORMAL;
				backgroundList[maxFish + 2]->m_nSpriteIndex = BUTTON_INFO_NORMAL;
				backgroundList[maxFish + 3]->m_nSpriteIndex = BUTTON_RELEASE_NORMAL;
			}
			else if (selectedFish.size() == 2)
			{
				backgroundList[maxFish]->m_nSpriteIndex = BUTTON_SELL_NORMAL;
				backgroundList[maxFish + 1]->m_nSpriteIndex = BUTTON_BREED_NORMAL;
				backgroundList[maxFish + 2]->m_nSpriteIndex = BUTTON_INFO_GRAY;
				backgroundList[maxFish + 3]->m_nSpriteIndex = BUTTON_RELEASE_NORMAL;
			}
			else
			{
				backgroundList[maxFish]->m_nSpriteIndex = BUTTON_SELL_NORMAL;
				backgroundList[maxFish + 1]->m_nSpriteIndex = BUTTON_BREED_NORMAL;
				backgroundList[maxFish + 2]->m_nSpriteIndex = BUTTON_INFO_GRAY;
				backgroundList[maxFish + 3]->m_nSpriteIndex = BUTTON_RELEASE_NORMAL;
			}
		}
		else if ((index >= maxFish) && (index < maxFish + 4))
		{
			if (backgroundList[index]->m_nSpriteIndex == BUTTON_SELL_HIGHLIGHTED)
			{
				int total = 0;
				
				for (auto& i : selectedFish)
				{
					total += ((FishObject*)i)->getPrice();
				}
				dialogBox = new DialogObject(Vector3(PC->m_vPos.x, PC->m_vPos.y, 1000), SELL_DIALOG, total);
				dialogBox->setDialog();
				isDialogOpen = true;
			}
			else if (backgroundList[index]->m_nSpriteIndex == BUTTON_INFO_HIGHLIGHTED)
			{
				dialogBox = new DialogObject(Vector3(PC->m_vPos.x, PC->m_vPos.y, 1000), INFO_DIALOG);
				dialogBox->setDialog();
				isDialogOpen = true;
			}
			else if (backgroundList[index]->m_nSpriteIndex == BUTTON_BREED_HIGHLIGHTED) 
			{
				dialogBox = new DialogObject(Vector3(PC->m_vPos.x, PC->m_vPos.y, 1000), BREED_DIALOG);
				//if (selectedFish.size() < 2) dialogBox->setDialog(0);
				//else if (selectedFish.size() == 2) dialogBox->setDialog(1);
				//else if (selectedFish.size() > 2) dialogBox->setDialog(2);
				dialogBox->setDialog(4);
				isDialogOpen = true;
			}
			else if (backgroundList[index]->m_nSpriteIndex == BUTTON_RELEASE_HIGHLIGHTED) 
			{
				dialogBox = new DialogObject(Vector3(PC->m_vPos.x, PC->m_vPos.y, 1000), RELEASE_DIALOG);
				dialogBox->setDialog();
				isDialogOpen = true;
			}
		}
	}
	else
	{
		int result = dialogBox->handleMouseClick(p); //forward the click to the dialog for a response
		bool showSecondDialog = false;

		if (dialogBox->type == RELEASE_DIALOG)
		{
			if (result == 1)
			{
				for (auto i = selectedFish.begin(); i != selectedFish.end(); ++i)
				{
					for (auto j = menuFishList.begin(); j != menuFishList.end(); ++j)
					{
						if (*i == *j)
						{
							(*j)->m_vPos = (*j)->originalPoint;
							(*j)->isCaught = false;
							(*j)->isHooked = false;
							(*j)->m_fXScale = (*j)->originalXScale;
							(*j)->m_fYScale = (*j)->originalYScale;
							m_pObjectManager->m_fishObjectList.push_back(*j);
							menuFishList.erase(j);
							--numFish;
							setInventoryPositions();
							break;
						}
					}
				}
				resetMenuBackground();

				for (index = 0; index < maxFish; ++index)
				{
					if (backgroundList[index]->m_nSpriteIndex == SELECT_HOVER_INVENTORY_BACKGROUND) backgroundList[index]->m_nSpriteIndex = HOVER_INVENTORY_BACKGROUND;
					else if (backgroundList[index]->m_nSpriteIndex == SELECT_INVENTORY_BACKGROUND) backgroundList[index]->m_nSpriteIndex = NORMAL_INVENTORY_BACKGROUND;
				}

				backgroundList[maxFish]->m_nSpriteIndex = BUTTON_SELL_GRAY;
				backgroundList[maxFish + 1]->m_nSpriteIndex = BUTTON_BREED_NORMAL;
				backgroundList[maxFish + 2]->m_nSpriteIndex = BUTTON_INFO_GRAY;
				backgroundList[maxFish + 3]->m_nSpriteIndex = BUTTON_RELEASE_GRAY;
			}
		}
		else if (dialogBox->type == SELL_DIALOG)
		{
			
			int total = 0;
			if (result == 1)
			{
				m_pAudio->play(MONEY);
				for (auto i = selectedFish.begin(); i != selectedFish.end(); ++i)
				{
					total += ((FishObject*)*i)->getPrice();
					for (auto j = menuFishList.begin(); j != menuFishList.end(); ++j)
					{
						if (*i == *j)
						{
							delete* j;
							menuFishList.erase(j);
							--numFish;
							setInventoryPositions();
							break;
						}
					}
				}
				resetMenuBackground();
				m_pObjectManager->addCurrency(total);
			}
		}
		else if (dialogBox->type == BREED_DIALOG)
		{
			if ((result == 1)) //maybe make a pink background
			{
				resetMenuBackground();
				showSecondDialog = true;
			}
		}
		if ((result == 1) || (result == 2))
		{
			delete dialogBox;
			dialogBox = nullptr;

			isDialogOpen = false;
			//handle result
		}
		if (showSecondDialog)
		{
			dialogBox = new DialogObject(Vector3(PC->m_vPos.x, PC->m_vPos.y, 1000), BREED_DIALOG);
			//dialogBox->setDialog(3);
			dialogBox->setDialog(5);
			isDialogOpen = true;
		}
	}
	//printf("X:%f Y%f\n", (p.x - (m_nWinWidth / 2) + (int)PC->m_vPos.x) * 0.625, 0.63 *((m_nWinHeight - p.y ) - 402)) ;
}

void MenuObject::handleGearHover(POINT p)
{
	int x = ((p.x - (m_nWinWidth / 2)) * 0.625) + (int)PC->m_vPos.x;
	int y = 0.63 * ((m_nWinHeight - p.y) - 402);
	int index = 0;
	int highlightedIndex = -1;

	if (!isDialogOpen)
	{
		for (auto i : gearPositions)
		{
			if (index < 12) // the gear menu will only have 18 positions
			{
				if ((x > (PC->m_vPos.x + offset + i.x) - 24) && (x < (PC->m_vPos.x + offset + i.x) + 24))
				{
					if ((y > i.y - 22) && (y < i.y + 22)) highlightedIndex = index;
				}
			}
			else //this is for the button to be highlighted
			{
				if ((x > (PC->m_vPos.x + offset + i.x) - 35) && (x < (PC->m_vPos.x + offset + i.x) + 35)) //the buy button
				{
					if ((y > i.y - 10) && (y < i.y + 10))
					{
						highlightedIndex = index;
					}
				}
			}
			if (gearBackgroundList[index]->m_nSpriteIndex == HOVER_ITEM_BACKGROUND) gearBackgroundList[index]->m_nSpriteIndex = NORMAL_ITEM_BACKGROUND;
			else if (gearBackgroundList[index]->m_nSpriteIndex == SELECT_HOVER_ITEM_BACKGROUND) gearBackgroundList[index]->m_nSpriteIndex = SELECT_ITEM_BACKGROUND;
			else if (gearBackgroundList[index]->m_nSpriteIndex == BUTTON_BUY_HIGHLIGHTED) gearBackgroundList[index]->m_nSpriteIndex = BUTTON_BUY_NORMAL;
			else if (gearBackgroundList[index]->m_nSpriteIndex == BUTTON_SELECT_HIGHLIGHTED) gearBackgroundList[index]->m_nSpriteIndex = BUTTON_SELECT_NORMAL;

			++index;
		}
		if (highlightedIndex >= 0)
		{
			if (gearBackgroundList[highlightedIndex]->m_nSpriteIndex == NORMAL_ITEM_BACKGROUND) gearBackgroundList[highlightedIndex]->m_nSpriteIndex = HOVER_ITEM_BACKGROUND;
			else if (gearBackgroundList[highlightedIndex]->m_nSpriteIndex == SELECT_ITEM_BACKGROUND) gearBackgroundList[highlightedIndex]->m_nSpriteIndex = SELECT_HOVER_ITEM_BACKGROUND;
			else if (gearBackgroundList[highlightedIndex]->m_nSpriteIndex == BUTTON_BUY_NORMAL) gearBackgroundList[highlightedIndex]->m_nSpriteIndex = BUTTON_BUY_HIGHLIGHTED;
			else if (gearBackgroundList[highlightedIndex]->m_nSpriteIndex == BUTTON_SELECT_NORMAL) gearBackgroundList[highlightedIndex]->m_nSpriteIndex = BUTTON_SELECT_HIGHLIGHTED;

		}
	}
	else dialogBox->handleMouseHover(p);
}

void MenuObject::handleGearClick(POINT p)
{
	int x = ((p.x - (m_nWinWidth / 2)) * 0.625) + (int)PC->m_vPos.x;
	int y = 0.63 * ((m_nWinHeight - p.y) - 402);
	int index = 0;

	if (!isDialogOpen)
	{
		for (auto i : gearPositions)
		{
			if (index < 12)
			{
				if ((x > (PC->m_vPos.x + offset + i.x) - 24) && (x < (PC->m_vPos.x + offset + i.x) + 24))
				{
					if ((y > i.y - 22) && (y < i.y + 22))
					{
						m_pAudio->play(SELECT);
						break;
					}
				}
			}
			else
			{
				if ((x > (PC->m_vPos.x + offset + i.x) - 35) && (x < (PC->m_vPos.x + offset + i.x) + 35)) //the buy button
				{
					if ((y > i.y - 10) && (y < i.y + 10))
					{
						m_pAudio->play(SELECT);
						break;
					}
				}
			}
			++index;
		}
		if (index < 12) //boat click
		{
			for (int i = 0; i < 12; ++i) //only one selection can be made at a time.
			{
				if (gearBackgroundList[i]->m_nSpriteIndex == SELECT_ITEM_BACKGROUND) gearBackgroundList[i]->m_nSpriteIndex = NORMAL_ITEM_BACKGROUND;
				if (gearBackgroundList[i]->m_nSpriteIndex == SELECT_HOVER_ITEM_BACKGROUND) gearBackgroundList[i]->m_nSpriteIndex = HOVER_ITEM_BACKGROUND;
			}
			if (gearBackgroundList[index]->m_nSpriteIndex == HOVER_ITEM_BACKGROUND) //we added it to our selection
			{
				gearBackgroundList[index]->m_nSpriteIndex = SELECT_HOVER_ITEM_BACKGROUND;
			}
			else if (gearBackgroundList[index]->m_nSpriteIndex == SELECT_HOVER_ITEM_BACKGROUND) //we removed it from our selection
			{
				gearBackgroundList[index]->m_nSpriteIndex = HOVER_ITEM_BACKGROUND;
			}	

			if (index < 3)
			{
				highlightedBoat = true;
				highlightedFishingPole = false;
				highlightedWeight = false;
				highlightedSprite = boatList[index].sprite;

				if (boatList[index].hasPurchased)
				{
					gearBackgroundList[12]->m_nSpriteIndex = BUTTON_SELECT_NORMAL;
					gearBackgroundList[13]->m_nSpriteIndex = BUTTON_BUY_GRAY;
				}
				else
				{
					gearBackgroundList[12]->m_nSpriteIndex = BUTTON_SELECT_GRAY;
					gearBackgroundList[13]->m_nSpriteIndex = BUTTON_BUY_NORMAL;
				}			
			}
			else if (index < 9)
			{
				highlightedBoat = false;
				highlightedFishingPole = true;
				highlightedWeight = false;
				highlightedSprite = poleList[index - 3].sprite;

				if (poleList[index - 3].hasPurchased)
				{
					gearBackgroundList[12]->m_nSpriteIndex = BUTTON_SELECT_NORMAL;
					gearBackgroundList[13]->m_nSpriteIndex = BUTTON_BUY_GRAY;
				}
				else
				{
					gearBackgroundList[12]->m_nSpriteIndex = BUTTON_SELECT_GRAY;
					gearBackgroundList[13]->m_nSpriteIndex = BUTTON_BUY_NORMAL;
				}
			}
			else if (index < 12)
			{
				highlightedBoat = false;
				highlightedFishingPole = false;
				highlightedWeight = true;
				highlightedSprite = weightList[index - 9].sprite;

				if (weightList[index - 9].hasPurchased)
				{
					gearBackgroundList[12]->m_nSpriteIndex = BUTTON_SELECT_NORMAL;
					gearBackgroundList[13]->m_nSpriteIndex = BUTTON_BUY_GRAY;
				}
				else
				{
					gearBackgroundList[12]->m_nSpriteIndex = BUTTON_SELECT_GRAY;
					gearBackgroundList[13]->m_nSpriteIndex = BUTTON_BUY_NORMAL;
				}

			}
		}
		else if (index < gearPositions.size())
		{
			if (gearBackgroundList[index]->m_nSpriteIndex == BUTTON_SELECT_HIGHLIGHTED)
			{
				if (highlightedBoat) selectedBoat = highlightedSprite;
				else if (highlightedFishingPole) selectedFishingPole = highlightedSprite;
				else if (highlightedWeight) selectedWeight = highlightedSprite;
			}
			else if (gearBackgroundList[index]->m_nSpriteIndex == BUTTON_BUY_HIGHLIGHTED)
			{
				int dialog;
				if (highlightedBoat)
				{
					for (int i = 0; i < boatList.size(); ++i)
					{
						if (boatList[i].sprite == highlightedSprite) dialog = i;
					}
				}
				else if (highlightedFishingPole)
				{
					for (int i = 0; i < poleList.size(); ++i)
					{
						if (poleList[i].sprite == highlightedSprite) dialog = i + 3;
					}
				}
				else if (highlightedWeight)
				{
					for (int i = 0; i < weightList.size(); ++i)
					{
						if (weightList[i].sprite == highlightedSprite) dialog = i + 9;
					}
				}

				dialogBox = new DialogObject(Vector3(PC->m_vPos.x, PC->m_vPos.y, 1000), BUY_DIALOG);
				dialogBox->setDialog(dialog);
				isDialogOpen = true;
				
			}
		}
	}
	else
	{
		int result = dialogBox->handleMouseClick(p);
		bool showSecondDialog = false;
		
		if (dialogBox->type == BUY_DIALOG)
		{
			
			if (result == 1)
			{
				int amount = dialogBox->buyPrice;
				if (abs(amount) > m_pObjectManager->getPlayerCurrency()) showSecondDialog = true;
				else
				{
					int index;
					if (highlightedBoat)
					{
						for (int i = 0; i < boatList.size(); ++i)
						{
							if (boatList[i].sprite == highlightedSprite)
							{
								boatList[i].hasPurchased = true;
								m_pObjectManager->addCurrency(dialogBox->buyPrice);
								m_pAudio->play(MONEY);
							}
						}
					}
					else if (highlightedFishingPole)
					{
						for (int i = 0; i < poleList.size(); ++i)
						{
							if (poleList[i].sprite == highlightedSprite)
							{
								poleList[i].hasPurchased = true;
								m_pObjectManager->addCurrency(dialogBox->buyPrice);
								m_pAudio->play(MONEY);
							}
						}
					}
					else if (highlightedWeight)
					{
						for (int i = 0; i < weightList.size(); ++i)
						{
							if (weightList[i].sprite == highlightedSprite)
							{
								weightList[i].hasPurchased = true;
								m_pObjectManager->addCurrency(dialogBox->buyPrice);
								m_pAudio->play(MONEY);
							}
						}
					}
				}
			}
		}
		if ((result == 1) || (result == 2))
		{
			delete dialogBox;
			dialogBox = nullptr;

			isDialogOpen = false;
			//handle result
		}
		if (showSecondDialog)
		{
			dialogBox = new DialogObject(Vector3(PC->m_vPos.x, PC->m_vPos.y, 1000), FAIL_DIALOG);
			dialogBox->setDialog();
			isDialogOpen = true;
		}
	}
}

bool MenuObject::toggleMenu(POINT p)
{
	//inventory
	if ((p.x >= m_nWinWidth * 0.96640625) && (p.x <= m_nWinWidth) && (p.y >= m_nWinHeight * 0.0097222) && (p.y <= m_nWinHeight * 0.059722) && (menuOpen == false))
	{
		m_nSpriteIndex = INVENTORY_MENU;
	}
	if ((p.x >= m_nWinWidth * 0.78359375) && (p.x <= m_nWinWidth * 0.815625) && (p.y >= m_nWinHeight * 0.0097222) && (p.y <= m_nWinHeight * 0.059722) && (menuOpen == true))
	{
		if (m_nSpriteIndex != INVENTORY_MENU)
		{
			m_nSpriteIndex = INVENTORY_MENU;
			return menuOpen;
		}
	}

	//Breeding
	if ((p.x >= m_nWinWidth * 0.96640625) && (p.x <= m_nWinWidth) && (p.y >= m_nWinHeight * 0.066666) && (p.y <= m_nWinHeight * 0.1097222) && (menuOpen == false))
	{
		m_nSpriteIndex = BREEDING_MENU;
	}
	if ((p.x >= m_nWinWidth * 0.78359375) && (p.x <= m_nWinWidth * 0.815625) && (p.y >= m_nWinHeight * 0.0666666) && (p.y <= m_nWinHeight * 0.1097222) && (menuOpen == true))
	{
		if (m_nSpriteIndex != BREEDING_MENU)
		{
			m_nSpriteIndex = BREEDING_MENU;
			return menuOpen;
		}
	}

	//Gear
	if ((p.x >= m_nWinWidth * 0.96640625) && (p.x <= m_nWinWidth) && (p.y >= m_nWinHeight * 0.1236112) && (p.y <= m_nWinHeight * 0.1597224) && (menuOpen == false))
	{
		m_nSpriteIndex = GEAR_MENU;
	}
	if ((p.x >= m_nWinWidth * 0.78359375) && (p.x <= m_nWinWidth * 0.815625) && (p.y >= m_nWinHeight * 0.1236112) && (p.y <= m_nWinHeight * 0.1597224) && (menuOpen == true))
	{
		if (m_nSpriteIndex != GEAR_MENU)
		{
			m_nSpriteIndex = GEAR_MENU;
			return menuOpen;
		}
	}

	if (menuOpen == false)
	{
		m_pAudio->play(MENU_OPEN, 3.0);
		m_fSpeed = -1.5;
	}

	else
	{
		m_pAudio->play(MENU_CLOSE, 3.0);
		m_fSpeed = 1.5;
	}
	menuOpen = !menuOpen;
	return menuOpen;
}

bool MenuObject::toggleMenu(eSpriteType t)
{
	if (menuOpen == false)
	{
		menuOpen = !menuOpen;
		m_nSpriteIndex = t;
		m_fSpeed = 2.2f;
		m_pAudio->play(MENU_OPEN, 3.0);
	}
	else
	{
		if (m_nSpriteIndex == t) menuOpen = !menuOpen;
		else m_nSpriteIndex = t;
		m_fSpeed = -2.2f;
		m_pAudio->play(MENU_CLOSE, 3.0);
	}
	return menuOpen;
}

void MenuObject::setInventoryPositions()
{
	displayList.clear();
	
	int index = 0;
	for (auto& i : backgroundList)
	{
		i->m_vPos = inventoryPositions[index];
		i->m_vPos.y += 1;
		++index; ///this shouldnt reach past the allocated memory because we return if we cant add to maxFish. CHECK THERE FIRST.

		displayList.push_back((CSpriteDesc3D*)i);
	}
	index = 0;
	for (auto& i : menuFishList)
	{
		i->m_vPos = inventoryPositions[index];
		i->m_vPos.z -= 1;
		++index; ///this shouldnt reach past the allocated memory because we return if we cant add to maxFish. CHECK THERE FIRST.

		displayList.push_back((CSpriteDesc3D*)i);
	}
}

void MenuObject::setGearPositions()
{
	gearDisplayList.clear();

	int index = 0;
	for (auto& i : gearBackgroundList)
	{
		i->m_vPos = gearPositions[index];
		i->m_vPos.y += 1;
		++index; ///this shouldnt reach past the allocated memory because we return if we cant add to maxFish. CHECK THERE FIRST.

		gearDisplayList.push_back((CSpriteDesc3D*)i);
	}

	index = 0;
 	for (auto& i : boatList)
	{
		i.sprite->m_vPos = gearPositions[index];
		i.sprite->m_vPos.y += 1;
		++index;
		gearDisplayList.push_back(i.sprite);

	}
	for (auto& i : weightList)
	{
		i.sprite->m_vPos = gearPositions[index];
		i.sprite->m_vPos.y += 1;
		++index; 
		gearDisplayList.push_back(i.sprite);

	}
	for (auto& i : poleList)
	{
		i.sprite->m_vPos = gearPositions[index];
		i.sprite->m_vPos.y += 1;
		++index; 
		gearDisplayList.push_back(i.sprite);
	}
	index = 0;
	for (auto& i : gearLocks)
	{
		i->m_vPos = gearPositions[index];
		i->m_vPos.y -= 1;
		++index;
		gearDisplayList.push_back(i);
	}
	
	//items

	//locks
}

list<CSpriteDesc3D*> MenuObject::getDisplayList()
{
	switch (m_nSpriteIndex)
	{
	case INVENTORY_MENU:
		return displayList;
		break;
	case GEAR_MENU:
		return gearDisplayList;
		break;
	}
	return list<CSpriteDesc3D*>();
}

CObject* MenuObject::getDialogBox()
{
	return dialogBox;
}
