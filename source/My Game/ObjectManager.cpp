/// \file ObjectManager.cpp
/// \brief Code for the the object manager class CObjectManager.

#include "ObjectManager.h"
#include "TileManager.h"
#include "ComponentIncludes.h"
#include "ParticleEngine.h"
#include "FishObject.h"
#include "MenuObject.h"
#include "HookObject.h"

#include <ctime> //import time

/// Create the tile manager;

/* set sky and sea */
CObjectManager::CObjectManager() {
	prevFishingSprite->m_nSpriteIndex = PENGUIN_FISHING_SPRITE;
	menuOpen = false;
	savedTimeOffset = 900.0;
	currChunk = 22;

	fishingLine = new CSpriteDesc3D();
	//fishingLine->m_fXScale *= 3;
	//fishingLine->m_fYScale += 3;
	fishingLine->m_nSpriteIndex = WHITE_LINE;

	//make these variable, the 5. im having a hard time determining off of what at the moment
	worldStartChunk = middleChunkIndex - (5 * 1);
	worldEndChunk = middleChunkIndex + (5 * 1);
	world1Start = middleChunkIndex - (5 * 1);
	world1End = middleChunkIndex + (5 * 1);
	world2Start = middleChunkIndex - (5 * 2);
	world2End = middleChunkIndex + (5 * 2);
	world3Start = middleChunkIndex - (5 * 3);
	world3End = middleChunkIndex + (5 * 3);
	world4Start = middleChunkIndex - (5 * 4);
	world4End = middleChunkIndex + (5 * 4);
} //constructor

/// Destruct all of the objects in the object list.
CObjectManager::~CObjectManager() {
	for (auto const& p : m_stdObjectList) //for each object
		delete p; //delete object
	for (auto const& p : m_fishObjectList) //for each object
		delete p; //delete object
} //destructor

/// Create an object and put a pointer to it on the object list.
/// \param t Sprite type.
/// \param v Initial position.
/// \return Pointer to the object created.

CObject* CObjectManager::create(eSpriteType t, const Vector3& v, bool underWater) {
	CObject* p = nullptr;

	switch (t)
	{
	case HOOK_SPRITE:
		p = new HookObject(v, underWater);
		m_stdObjectList.push_back(p);
		return p;
	case CONNECTING_DOCK_SPRITE:
		//this will give it a 3d effect
		p = new CObject(t, v);
		p->m_fYScale *= 3;
		p->m_fPitch = 1.2;
		m_stdObjectList.insert(m_stdObjectList.begin(), p);

		//p = new CObject(CONNECTING_DOCK_3D_SPRITE, v);
		//p->m_fYScale *= 3;
		//p->m_fPitch = 1.2;
		break;
		//case SEA_ANIMATION:
		//	p = new CObject(t, v);
		//	p->m_fXScale = p->m_fYScale = m_fWorldScale;
		//	break;
	case BOAT1:
		boat = p = new CObject(UNLOADED_BOAT, v); //change to unloaded!
		p->boat = 1; //1 for unloaded as well.
		p->m_fXScale *= .35;
		p->m_fYScale *= .35;
		break;
	default:
		p = new CObject(t, v);
		
		break;
	}
	m_stdObjectList.insert(m_stdObjectList.begin(), p);
	return p;
} //create

CObject* CObjectManager::createFish(const Vector3& v, int seed)
{
	CObject* p = nullptr;

	p = new FishObject(v, 1, seed);
	int chunk = getChunk(p);
	if ((chunk <= world1End) && (chunk >= world1Start)) p->worldIndex = 1;
	else if ((chunk <= world2End) && (chunk >= world2Start)) p->worldIndex = 2;
	else if ((chunk <= world3End) && (chunk >= world3Start)) p->worldIndex = 3;
	else if ((chunk <= world4End) && (chunk >= world4Start)) p->worldIndex = 4;

	if ((p->m_vPos.x <= (PC->m_vPos.x + 1000)) && (p->m_vPos.x >= (PC->m_vPos.x - 1000)) && (p->m_vPos.y <= (PC->m_vPos.y + 1000)) && (p->m_vPos.y >= (PC->m_vPos.y - 1000)))
	{
		if ((int)p->GenerateSprite() > -1)
			m_pRenderer->LoadImages(p->m_nSpriteIndex, true);
	}
	m_fishObjectList.push_back(p);

	return p;
}

MenuObject* CObjectManager::createMenu(const Vector3& v)
{
	CObject* p = nullptr;

	//we will return the menu because that is what is being changed constantly (isOpen)
	//but we need to create the entire HUD in this function. quite honestly, im worried we have too many redundant functions as it is.
	currencyBar = new CurrencyBarObject(Vector3(0, 0, 1000));
	m_HUDList.push_back(currencyBar);
	timeBar = new TimeBarObject(Vector3(0, 0, 1000));
	m_HUDList.push_back(timeBar);
	p = new MenuObject(v);
	m_HUDList.push_back(p);

	currencyBar->setCurrency(0);

	return (MenuObject*)p;
}

void CObjectManager::createStartPage()
{
	////display the start game screen, which is different based on time //FIXME: time¾ÆÁ÷ ¾È¸¸µë. °Á Ä«ÇÇÇÔ µÊ.
	//backwardChunk = m_pTileManager->getBackwardChunk();
	//background.m_nSpriteIndex = START_PAGE1;
	//background.m_vPos = Vector3(0, -900, 2199);
	//background.m_fXScale *= 8;
	//background.m_fYScale *= 5;
	////display the setting, credit, and click to start
	
}

void CObjectManager::createEnvironment()
{
	forwardChunk = m_pTileManager->getForwardChunk();
	currentChunk = m_pTileManager->getCurrentChunk();
	backwardChunk = m_pTileManager->getBackwardChunk();
	fill = m_pTileManager->getFill();

	hue.m_nSpriteIndex = SKY_HUE;
	night.m_nSpriteIndex = NIGHT_OVERLAY;
	background.m_nSpriteIndex = OCEAN_BACKDROP;
	sky.m_nSpriteIndex = BASE_SKY;
	shadow.m_nSpriteIndex = NIGHT_SHADE;
	foreground.m_nSpriteIndex = FOREGROUND;

	sky.m_fXScale = sky.m_fYScale = m_fWorldScale;
	hue.m_fXScale = hue.m_fYScale = m_fWorldScale;
	night.m_fXScale = night.m_fYScale = m_fWorldScale;

	sky.m_vPos = Vector3(0, 0, 2200.0f);
	background.m_vPos = Vector3(0, -900, 2199);
	foreground.m_vPos = Vector3(0, -614, 1987);

	background.m_fXScale *= 8;
	background.m_fYScale *= 5;
	foreground.m_fXScale *= 8;
	foreground.m_fYScale *= 4;
	shadow.m_fXScale *= 8;
	shadow.m_fYScale *= 4;

	sun.m_vPos = Vector3(0, -75, 2200.0f);

	//this is where we will load the saved time from a file from the users previous save.
	//LoadSavedTime()
	//CHECK THESE thoroughly
	//night time case
	currentTime = savedTimeOffset;
	if (((currentTime <= 650) && (currentTime >= 0)) || (currentTime >= 1950))
	{
		sun.m_nSpriteIndex = FULL_MOON_SPRITE;
		night.m_fAlpha = 1.0;
		shadow.m_fAlpha = 0.5f;
		hueOffset = 1000;
	}
	//day time case
	else if ((currentTime >= 750) && (currentTime < 1850))
	{
		sun.m_nSpriteIndex = SUN_SPRITE;
		night.m_fAlpha = 0.0;
		shadow.m_fAlpha = 0.0f;
		hueOffset = -1000;
	}
	//dawn case
	else if ((currentTime >= 550) && (currentTime < 750))
	{ //sun rising, hue limit is -1000
		float ratio = ((currentTime - 550.0) * 10.0) / 2000.0; //lets work with parts to keep this easier, the hue moved 2000 units per dawn/twilight cycle and the alpha of night should behave similarly with 1000 units
		hueOffset = -(2000.0 * ratio);
		night.m_fAlpha = 1.0 - (2 * ratio);
		shadow.m_fAlpha = night.m_fAlpha / 2;
		if ((night.m_fAlpha < 0.0f) || (shadow.m_fAlpha < 0.0f))
		{
			night.m_fAlpha = 0.0f;
			shadow.m_fAlpha = 0.0f;
		}
	}
	//twilight case
	else if ((currentTime >= 1750) && (currentTime < 1950))
	{ //sun setting, hue limit is 1000
		float ratio = ((currentTime - 1750.0) * 10.0) / 2000.0;
		hueOffset = -1000 + (2000.0 * ratio);
		night.m_fAlpha = ratio;
		shadow.m_fAlpha = ratio / 2;
	}
	foreground.m_fAlpha = 0.25;
}

int CObjectManager::getChunk(CObject* p0)
{
	return int((p0->m_vPos.x + (m_fWorldWidth / 2)) / 2000);
}

int CObjectManager::getPlayerCurrency()
{
	return currencyBar->getCurrency();
}

void CObjectManager::loadAndUnloadFish()
{
	for (auto& p : m_fishObjectList) { //for each object
		p->seed += 5;
		p->GenerateSprite();
		m_pRenderer->LoadImages(p->m_nSpriteIndex, true);
	}
}

void CObjectManager::addCurrency(int amount)
{
	currencyBar->addCurrency(amount);	
}

void CObjectManager::DrawForeground()
{
	m_pRenderer->Draw(foreground);

	shadow.m_vPos = Vector3(PC->m_vPos.x, PC->m_vPos.y, 1001);
	m_pRenderer->Draw(shadow);

	for (auto const& p : m_HUDList) { //for each object
		m_pRenderer->Draw(*(CSpriteDesc3D*)p);
		
		
		for (auto const& q : p->getDisplayList())
		{
			if (q != nullptr)
			{
				m_pRenderer->Draw(*(CSpriteDesc3D*)q);
			}
		}

		if (p == menu)
		{
			CObject* dialogBox = (*(MenuObject*)p).getDialogBox();
			if (dialogBox != nullptr)
			{
				m_pRenderer->Draw(*(CSpriteDesc3D*)dialogBox);
				for (auto const& q : dialogBox->getDisplayList())
				{
					if (q != nullptr)
					{
						m_pRenderer->Draw(*(CSpriteDesc3D*)q);
					}
				}
			}
		}		
	} //for
}

void CObjectManager::DrawBackground()
{
	DrawBackground(sky);
}

void CObjectManager::DrawBackground(CSpriteDesc3D& sd) {
	if (PC->m_nSpriteIndex != HOOK_SPRITE && PC->m_nSpriteIndex != WHITE_LINE && PC->m_nSpriteIndex < NUM_SPRITES) // this locks the sky to the penguin PC
	{
		sky.m_vPos = Vector3(PC->m_vPos.x, PC->m_vPos.y + 75, sky.m_vPos.z);
		night.m_vPos = sky.m_vPos;
		background.m_vPos = Vector3(PC->m_vPos.x, PC->m_vPos.y - 600, sky.m_vPos.z);
	}
	else if (PC->m_vPos.y < -600.0f)
	{
		background.m_vPos = Vector3(PC->m_vPos.x, PC->m_vPos.y, 2199.0f);
		foreground.m_fAlpha = 0.25 + (0.0001 * fabs(PC->m_vPos.y + 600.0)); //deeper is darker
	}
	if (PC->m_vPos.y < -570.0f) foreground.m_vPos = Vector3(PC->m_vPos.x, PC->m_vPos.y, 1500.0f);
	else foreground.m_vPos = Vector3(0, -614, 1987);

	sky.m_vPos.x = PC->m_vPos.x;
	night.m_vPos.x = PC->m_vPos.x;
	background.m_vPos.x = PC->m_vPos.x;
	foreground.m_vPos.x = PC->m_vPos.x;
	hue.m_vPos = Vector3(sky.m_vPos.x, sky.m_vPos.y - hueOffset, sky.m_vPos.z);
	sun.m_vPos.x = PC->m_vPos.x;
	//move hue based on time to simulate sun rise and set
	//0000 is midnight and 1200 is noon. So sunrise is at 0600 and twilight is at 1800
	//we want the hue to cycle for 1 hour, so from 0630 to 0730 and 1730 to 1830
	//1660 is the offset for sunrise and -340 for sunset
	//float newTime = fmod(m_pStepTimer->GetTotalSeconds(), 2400);
	float newTime = (round(10 * (m_pStepTimer->GetTotalSeconds())) / 10) + savedTimeOffset;
	newTime = fmod(newTime, 2400);
	if (currentTime != newTime)
	{
		timeBar->setTime(newTime);
		currentTime = (newTime);
		
		//set daytime and nighttime
		if ((currentTime >= 550) && (currentTime < 750))
		{
			hueOffset -= 1;
			if (night.m_fAlpha > 0.0000f) night.m_fAlpha -= 0.0005f;
			if (shadow.m_fAlpha > 0.00000f) shadow.m_fAlpha -= 0.00025f;
		}
		else if ((currentTime >= 1750) && (currentTime < 1950))
		{
			hueOffset += 1;
			if (night.m_fAlpha < 1.0000f) night.m_fAlpha += 0.0005f;
			if (shadow.m_fAlpha < 0.50000f) shadow.m_fAlpha += 0.00025f;
		}

		//convert time to minutes and hours
		float minutes = ((fmod(newTime, 100)) / 100.0) * 60.0;
		float hours = newTime / 100;
	}

	if (currentTime > 750 && currentTime <= 1350)
	{
		//sun rising
		sun.m_nSpriteIndex = SUN_SPRITE;
		sun.m_vPos.y = -175 + (600 - (1350 - currentTime));
		//sky and ocean setting
		//sky.m_nSpriteIndex = BASE_SKY2;
		//background.m_nSpriteIndex = OCEAN_BACKDROP2;
	}
	else if (currentTime > 1350 && currentTime <= 1950)
	{
		//sun setting
		sun.m_nSpriteIndex = SUN_SPRITE;
		sun.m_vPos.y = -175 + ((1950 - currentTime));
//sky and ocean setting
//sky.m_nSpriteIndex = BASE_SKY3;
//background.m_nSpriteIndex = OCEAN_BACKDROP3;

	}
	else if (currentTime > 1950 || currentTime <= 150)
	{
	//moon rising
	sun.m_nSpriteIndex = FULL_MOON_SPRITE;
	int temp = int(currentTime + 450) % 2400;
	sun.m_vPos.y = -175 + (600 - ((600 - temp)));
	//sky and ocean setting
	//sky.m_nSpriteIndex = BASE_SKY4;
	//background.m_nSpriteIndex = OCEAN_BACKDROP4;
	}
	else if (currentTime > 150 && currentTime <= 750)
	{
	//moon setting
	sun.m_nSpriteIndex = FULL_MOON_SPRITE;
	sun.m_vPos.y = -175 + ((750 - currentTime));
	//sky and ocean setting
	//sky.m_nSpriteIndex = BASE_SKY;
	//background.m_nSpriteIndex = OCEAN_BACKDROP1;
	}

	//change environment based on ocean. nothing too fancy, not enough time to fade them.
	if ((getChunk(PC) >= world1Start) && (getChunk(PC) <= world1End))
	{
		sky.m_nSpriteIndex = BASE_SKY;
		background.m_nSpriteIndex = OCEAN_BACKDROP;
	}
	else if ((getChunk(PC) >= world2Start) && (getChunk(PC) <= world2End))
	{
		sky.m_nSpriteIndex = BASE_SKY_YELLOW;
		background.m_nSpriteIndex = OCEAN_BACKDROP_YELLOW;
	}

	m_pRenderer->Draw(hue);
	m_pRenderer->Draw(sky);
	m_pRenderer->Draw(night);
	m_pRenderer->Draw(sun);
	m_pRenderer->Draw(background);
} //DrawBackground

void CObjectManager::DrawLine(Vector3 point1, Vector3 point2)
{
	float y0, y1, x0, x1;

	if (point1.x < point2.x)
	{
		y0 = point1.y;
		y1 = point2.y;

		x0 = point1.x;
		x1 = point2.x;
	}
	else
	{
		y0 = point2.y;
		y1 = point1.y;

		x0 = point2.x;
		x1 = point1.x;
	}

	float m = (y1 - y0) / (x1 - x0);
	float b = y0 - (m * x0);
	int y, nextY;
	for (int j = x0; j < x1 - 1; ++j) //we need to draw up to the next line portion
	{
		if (point1.x < point2.x)
		{
			y = (m * (j)) + b;
			nextY = (m * (j + 1)) + b;
			while (y <= nextY)
			{
				fishingLine->m_vPos = Vector3(j, y++, point1.z);
				m_pRenderer->Draw(*fishingLine);
			}
		}
		else
		{
			y = (m * (j)) + b;
			nextY = (m * (j + 1)) + b;
			while (y >= nextY)
			{
				fishingLine->m_vPos = Vector3(j, y--, point1.z);
				m_pRenderer->Draw(*fishingLine);
			}
		}
		fishingLine->m_vPos = Vector3(j, (m * j) + b, point1.z);
		m_pRenderer->Draw(*fishingLine);
	}
}

// Delete all of the objects managed by the object manager.
/// This involves deleting all of the CObject instances pointed
/// to by the object list, then clearing the object list itself.

void CObjectManager::clear() {
	for (auto const& p : m_stdObjectList) //for each object
		delete p; //delete object
	for (auto const& p : m_fishObjectList) //for each object
		delete p; //delete object
	m_stdObjectList.clear(); //clear the object list
	m_fishObjectList.clear();
} //clear

/// Draw the tiled background and all of the objects.

void CObjectManager::draw() { //this should only draw in the chunk
	Vector3 penguinPos;
	for (auto const& p : m_stdObjectList) { //for each object
		if (p->isBoarded == false) m_pRenderer->Draw(*(CSpriteDesc3D*)p);

		if (p->m_nSpriteIndex == PENGUIN_FISHING_SPRITE) penguinPos = p->m_vPos;
		if (p->m_nSpriteIndex == DOCK_BACK)
		{
			m_pRenderer->Draw(*forwardChunk);
			m_pRenderer->Draw(*currentChunk);
			m_pRenderer->Draw(*backwardChunk);

			fill->m_vPos = Vector3(currentChunk->m_vPos.x, currentChunk->m_vPos.y - (GetHeight(currentChunk->m_nSpriteIndex)) - (GetHeight(fill->m_nSpriteIndex)), currentChunk->m_vPos.z);
			m_pRenderer->Draw(*fill);
			fill->m_vPos = Vector3(forwardChunk->m_vPos.x, forwardChunk->m_vPos.y - (GetHeight(forwardChunk->m_nSpriteIndex)) - (GetHeight(fill->m_nSpriteIndex)), forwardChunk->m_vPos.z);
			m_pRenderer->Draw(*fill);
			fill->m_vPos = Vector3(backwardChunk->m_vPos.x, backwardChunk->m_vPos.y - (GetHeight(backwardChunk->m_nSpriteIndex)) - (GetHeight(fill->m_nSpriteIndex)), backwardChunk->m_vPos.z);
			m_pRenderer->Draw(*fill);
		}
	} //for
	if (PC->isBoarded == true)
	{
		m_pRenderer->Draw(*(CSpriteDesc3D*)PC);
		prevFishingSprite->m_vPos = PC->m_vPos;
	}
	else if ((PC->m_nSpriteIndex == WHITE_LINE) || (PC->m_nSpriteIndex >= NUM_SPRITES) || (PC->m_nSpriteIndex == HOOK_SPRITE))
	{
		printf("TRUE\n");
		m_pRenderer->Draw(*(CSpriteDesc3D*)prevFishingSprite);
	}

	//if the PC is not the penguin
	if ((PC->m_nSpriteIndex != PENGUIN_FISHING_SPRITE) && (PC->m_nSpriteIndex != PENGUIN_STOP_SPRITE) && (PC->m_nSpriteIndex != PENGUIN_LEFT_SPRITE) && (PC->m_nSpriteIndex != PENGUIN_RIGHT_SPRITE))
	{
		//draw the fishing line.
		DrawLine(Vector3(PC->m_vPos.x, PC->m_vPos.y, 1990), Vector3(penguinPos.x, penguinPos.y + 60, 1990));
	}
	for (auto& p : m_fishObjectList) { //for each object
		if (((p->m_vPos.x <= PC->m_vPos.x + 1000) && (p->m_vPos.x >= PC->m_vPos.x - 1000) && (p->m_vPos.y <= (PC->m_vPos.y + 1000)) && (p->m_vPos.y >= (PC->m_vPos.y - 1000))))
		{
			//if (doDrawFish((*(FishObject*)p)->feedingTime))
			//{
				if (p->worldIndex <= boat->boat)
				{
					if ((p->m_nSpriteIndex >= NUM_SPRITES) && (p->m_nSpriteIndex < (NUM_SPRITES + 512)))
						m_pRenderer->Draw(*(CSpriteDesc3D*)p);
					else printf("ERROR RENDERING FISH %d\n", p->m_nSpriteIndex);
				}
			//}
		}
	} //for
} //draw

void CObjectManager::generate()
{
	for (auto const& p : m_stdObjectList) { //for each object
		p->GenerateSprite();
		p->ProduceTestPNG();
	} //
}

bool CObjectManager::boardBoat(bool yes)
{
	if (yes)
	{	
		if (boat->m_nSpriteIndex != UNLOADED_BOAT)
		{
			if ((boat->m_vPos.x > -780) && (boat->m_vPos.x < 780))
			{
				if ((PC->m_vPos.x > boat->m_vPos.x - 250) && (PC->m_vPos.x < boat->m_vPos.x + 250))
				{
					PC->isBoarded = true;
					PC->m_vPos.x = boat->m_vPos.x;
					PC->m_vPos.z = 1987;
				}
			}
		}
	}
	else
	{
		if ((boat->m_vPos.x > -780) && (boat->m_vPos.x < 780))
		{
			PC->isBoarded = false;
			PC->m_vPos.z = 1990;
		}
	}
	return false;
}

CSpriteDesc3D* CObjectManager::getBoatType()
{
	switch (menu->selectedBoat->m_nSpriteIndex)
	{
	case ICON_BOAT_1:
		boat->m_nSpriteIndex = BOAT2;
		boat->boat = 1;
		break;
	case ICON_BOAT_2:
		boat->m_nSpriteIndex = BOAT2;
		boat->boat = 2;
		break;
	case ICON_BOAT_3:
		boat->m_nSpriteIndex = BOAT2;
		boat->boat = 2;
		break;
	}
	worldStartChunk = middleChunkIndex - (5 * boat->boat);
	worldEndChunk = middleChunkIndex + (5 * boat->boat);
	return menu->selectedBoat;
}

CSpriteDesc3D* CObjectManager::getPoleType()
{
	return menu->selectedFishingPole;
}

CSpriteDesc3D* CObjectManager::getWeightType()
{
	return menu->selectedWeight;
}

/// Move all of the objects and perform
/// broad phase collision detection and response.

void CObjectManager::move() {
	getBoatType();
	for (auto const& p : m_stdObjectList) //for each object
	{
		p->move(); //move it
		if (p == PC)
		{
			if (currChunk != getChunk(p))
			{
				currChunk = getChunk(p);

				if (currChunk == worldStartChunk - 1)
				{
					p->m_vPos.x += ((worldEndChunk - worldStartChunk) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					currChunk = worldEndChunk;
				}
				if (currChunk == worldEndChunk + 1)
				{
					p->m_vPos.x -= ((worldEndChunk - worldStartChunk) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					currChunk = worldStartChunk;
				}
				m_pTileManager->setChunk(currChunk);

				forwardChunk = m_pTileManager->getForwardChunk();
				currentChunk = m_pTileManager->getCurrentChunk();
				backwardChunk = m_pTileManager->getBackwardChunk();

				printf("%d\n", currChunk);
			}
		}
	}
	//now do object-object collision detection and response and
	//remove any dead objects from the object list.

	//loadAndUnloadFish();
	for (auto& p : m_fishObjectList) //for each object
	{
		p->move(); //move it
		if (p->isHooked == false)
		{
			int chunk = (getChunk(p));
			//Fish are bound to thier ocean. However the world wraps dynamically and causes issues with keeping fish in thier respective oceans
			//this is my solution for that. fish will wrap seemlessly around the largest ocean you can visit. smaller oceans will have thier fish fade in and out at the edges
			//and appear on the other side
			if ((getChunk(PC) != worldStartChunk) && (getChunk(PC) != worldEndChunk))
			{
				switch (p->worldIndex)
				{
				case 1:
					if (chunk > world1End) p->m_vPos.x -= ((world1End - world1Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					else if (chunk < world1Start) p->m_vPos.x += ((world1End - world1Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				case 2:
					if (chunk > world2End) p->m_vPos.x -= ((world2End - world2Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					else if (chunk < world2Start) p->m_vPos.x += ((world2End - world2Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					else if (chunk == world1End) p->m_vPos.x -= ((world1End - world1Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					else if (chunk == world1Start) p->m_vPos.x += ((world1End - world1Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				case 3:
					if (p->m_vPos.x >= ((world3End + 1) * m_fChunkSize - 200) - (m_fWorldWidth / 2))
						p->m_vPos.x -= ((world3End - world3Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					else if (p->m_vPos.x <= (world3Start * m_fChunkSize + 200) - (m_fWorldWidth / 2))
						p->m_vPos.x += ((world3End - world3Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				case 4:
					if (p->m_vPos.x >= ((world4End + 1) * m_fChunkSize - 200) - (m_fWorldWidth / 2))
						p->m_vPos.x -= ((world4End - world4Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					else if (p->m_vPos.x <= (world4Start * m_fChunkSize + 200) - (m_fWorldWidth / 2))
						p->m_vPos.x += ((world4End - world4Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				}
			}
			//this is for wrapping
			if (getChunk(PC) == worldStartChunk)
			{
				switch (p->worldIndex)
				{
				case 1:
					if ((boat->boat == 1) && (chunk == world1End)) p->m_vPos.x -= ((world1End - world1Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				case 2:
					if ((boat->boat == 2) && (chunk == world2End)) p->m_vPos.x -= ((world2End - world2Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				case 3:
					if ((boat->boat == 3) && (chunk == world3End)) p->m_vPos.x -= ((world3End - world3Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				case 4:
					if ((boat->boat == 4) && (chunk == world4End)) p->m_vPos.x -= ((world4End - world4Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				}
			}
			//this is for warapping
			else if (getChunk(PC) == worldEndChunk)
			{
				switch (p->worldIndex)
				{
				case 1:
					if ((boat->boat == 1) && (chunk == world1Start)) p->m_vPos.x += ((world1End - world1Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				case 2:
					if ((boat->boat == 2) && (chunk == world2Start)) p->m_vPos.x += ((world2End - world2Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				case 3:
					if ((boat->boat == 3) && (chunk == world3Start)) p->m_vPos.x += ((world3End - world3Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				case 4:
					if ((boat->boat == 4) && (chunk == world4Start)) p->m_vPos.x += ((world4End - world4Start) + 1) * m_fChunkSize + (5 * p->m_fSpeed);
					break;
				}
			}
		}
		if (((p->m_vPos.x <= PC->m_vPos.x + 1000) && (p->m_vPos.x >= PC->m_vPos.x - 1000) && (p->m_vPos.y <= (PC->m_vPos.y + 1000)) && (p->m_vPos.y >= (PC->m_vPos.y - 1000))) && (p->m_nSpriteIndex == UNLOADED_FISH_SPRITE) && (p->worldIndex <= boat->boat))
		{
			if (p->GenerateSprite() > -1)
			{
				m_pRenderer->LoadImages(p->m_nSpriteIndex, true);
			}
		}
		else if (((p->m_vPos.x > PC->m_vPos.x + 1000) || (p->m_vPos.x < PC->m_vPos.x - 1000) || (p->m_vPos.y > (PC->m_vPos.y + 1000)) || (p->m_vPos.y < (PC->m_vPos.y - 1000))) && (p->m_nSpriteIndex != UNLOADED_FISH_SPRITE))
		{
			if ((getChunk(p) <= worldStartChunk) || (getChunk(p) >= worldEndChunk)) {} //this is a hack, TODO figure out why the fish are moved back to the original spot, unloading, then moved to thier actual spot and loading
			else
			{
				if (int(p->m_nSpriteIndex - NUM_SPRITES) > -1) releaseSpriteIndex(p->m_nSpriteIndex - NUM_SPRITES);
				else printf("failed to unload fish sprite! %d\n", p->m_nSpriteIndex);
				p->m_nSpriteIndex = UNLOADED_FISH_SPRITE;
			}
		}
	}
	for (auto& p : m_HUDList) //for each object
	{
		p->move(); //move it
	}
	BroadPhase(); //broad phase collision detection and response
	CullDeadObjects(); //remove dead objects from object list
} //move

/// This is a "bring out yer dead" Monty Python type of thing.
/// Iterate through the objects and check whether their "is dead"
/// flag has been set. If so, then delete its pointer from
/// the object list and destruct the object.

void CObjectManager::CullDeadObjects() {
	for (auto i = m_stdObjectList.begin(); i != m_stdObjectList.end();) {
		if ((*i)->IsDead()) { //"He's dead, Dave." --- Holly, Red Dwarf
			delete* i; //delete object
			i = m_stdObjectList.erase(i); //remove from object list and advance to next object
		} //if

		else ++i; //advance to next object
	} //for
	for (auto i = m_fishObjectList.begin(); i != m_fishObjectList.end();) {
		if ((*i)->IsDead()) { //"He's dead, Dave." --- Holly, Red Dwarf
			delete* i; //delete object
			i = m_fishObjectList.erase(i); //remove from object list and advance to next object
		} //if
		else if ((*i)->isCaught) //this means that the menu will handle the fish for now.
		{
			menu->addFish(*i);
			i = m_fishObjectList.erase(i);
		}
		else ++i; //advance to next object
	} //for
} //CullDeadObjects

bool CObjectManager::doDrawFish(int feedingTime)
{
	bool result = false;
	switch (feedingTime)
	{
	case 0:
		if (currentTime > 750 && currentTime <= 1350)
		{
			result = true;
		}
		break;
	case 1:
		if (currentTime > 1350 && currentTime <= 1950)
		{
			result = true;
		}
		break;
	case 2:
		if (currentTime > 1950 || currentTime <= 150)
		{
			result = true;
		}
		break;
	case 3:
		if (currentTime > 150 && currentTime <= 750)
		{
			result = true;
		}
		break;
	}
	return result;
}

/// Perform collision detection and response for all pairs
/// of objects in the object list, making sure that each
/// pair is processed only once.

void CObjectManager::BroadPhase() {
	//check if hook is under fish
	if (PC->m_nSpriteIndex == HOOK_SPRITE)
	{
		if (m_pTileManager->testCollision(PC->m_vPos))
		{
			PC->SetSpeed(-10);
		}
	}
	if (PC->m_nSpriteIndex >= NUM_SPRITES) //fishies
	{
		if (m_pTileManager->testCollision(PC->m_vPos))
		{
			PC->isHooked = false;
			Vector3 anchor = PC->anchorPoint;
			PC = m_pObjectManager->create(HOOK_SPRITE, Vector3(PC->m_vPos.x, PC->m_vPos.y, PC->m_vPos.z), true);
			PC->m_nSpriteIndex = WHITE_LINE;
			PC->anchorPoint = anchor; //so the broken line goes back to the penguin instead of 0,0,0.
			PC->SetSpeed(-10);
			//play line snap
		}
	}

	for (auto i = m_fishObjectList.begin(); i != m_fishObjectList.end(); i++) {
		NarrowPhase(*i, PC);
	} //for
} //BroadPhase

/// Perform collision detection and response for a pair of objects.
/// \param p0 Pointer to the first object.
/// \param p1 Pointer to the second object.

void CObjectManager::NarrowPhase(CObject* p0, CObject* p1) {
	if (p0->m_nSpriteIndex > NUM_SPRITES && p1->m_nSpriteIndex == HOOK_SPRITE)
	{
		const float d = (p0->GetPos() - p1->GetPos()).Length();

		if (d < GetWidth(p0->m_nSpriteIndex) - 20) {
			p0->anchorPoint = PC->anchorPoint;
			PC->kill();
			PC = p0;
			PC->isHooked = true;
			m_pAudio->play(CATCH);
			//play hooked sound sound
		} //if
	} //if
} //NarrowPhase