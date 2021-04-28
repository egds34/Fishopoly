/// \file ObjectManager.h
/// \brief Interface for the object manager CObjectManager.

#pragma once

#include <list>

#include "Object.h"

#include "Component.h"
#include "Common.h"
#include "Settings.h"
#include "CurrencyBarObject.h"
#include "TimeBarObject.h"

using namespace std;

/// \brief The object manager.
/// A collection of all of the game objects.

class CObjectManager :
	public CComponent,
	public CCommon,
	public CSettings {
private:
	list<CObject*> m_stdObjectList; ///< Object list.
	
	list<CObject*> m_HUDList; //to be drawn in  the drawForeground function
	 //We need this because we have to constantly create and delete sprites based on the direction it is traveling.

	//background - its pretty complicated
	//we have a base sky layer that is half opaque and matches the theme of the ocean/world
	//we have a hue sprite that moved up and down depending on time and shows through the sky layer
	//we have another sky image that represent the night. this is always present but the opaqueness is full during night.
	//we need a blue square to follow the hook
	//we should probably put this all in a list.

	//Im not sure that we should put these in a list because they ll behave very specifically. perhaps we can make these an inherited object and make move cases
	CSpriteDesc3D sky;
	CSpriteDesc3D hue;
	CSpriteDesc3D night;
	CSpriteDesc3D background;
	CSpriteDesc3D foreground;
	CSpriteDesc3D shadow;
	CSpriteDesc3D sun;

	CSpriteDesc3D* forwardChunk;
	CSpriteDesc3D* currentChunk;
	CSpriteDesc3D* backwardChunk;
	CSpriteDesc3D* fill;

	CSpriteDesc3D* fishingLine = nullptr;
	
	CSpriteDesc3D* prevFishingSprite = new CSpriteDesc3D();

	int middleChunkIndex = 22;
	int world1Start, world1End;
	int world2Start, world2End;
	int world3Start, world3End;
	int world4Start, world4End;

	int hueOffset; //used to offset hue based on time
	
	CurrencyBarObject* currencyBar = nullptr;
	TimeBarObject* timeBar = nullptr;

	void BroadPhase(); ///< Broad phase collision detection and response.
	void NarrowPhase(CObject* p0, CObject* p1); ///< Narrow phase collision detection and response.
	void CullDeadObjects(); ///< Cull dead objects.
	bool doDrawFish(int feedingTime);

	bool menuOpen;
public:
	CObjectManager(); ///< Constructor.
	~CObjectManager(); ///< Destructor.

	list<CObject*> m_fishObjectList; ///< Object list.

	CObject* create(eSpriteType t, const Vector3& v, bool underWater = false); ///< Create new object.
	CObject* createFish(const Vector3& v, int seed); ///< Create new object.
	MenuObject* createMenu(const Vector3& v);
	CObject* createFish(const Vector3& v, CObject* mom, CObject* dad); ///< Create new object.
	
	void createStartPage();
	void createEnvironment();
	
	int currChunk = 22; //can be loaded in eventually
	int getChunk(CObject* p0);
	int getPlayerCurrency();

	void loadAndUnloadFish();

	void addCurrency(int amount);
	void DrawForeground();
	void DrawBackground();
	void DrawBackground(CSpriteDesc3D& backgroundsd);
	void DrawLine(Vector3 point1, Vector3 point2);

	void clear(); ///< Reset to initial conditions.
	void move(); ///< Move all objects. animate of sorts, might not be used

	void draw(); ///< Draw all objects.
	void generate();

	bool boardBoat(bool yes);

	CSpriteDesc3D* getBoatType();
	CSpriteDesc3D* getPoleType();
	CSpriteDesc3D* getWeightType();

	//The below variables should be public in order to be accessed by the getPrice function (which tells the fish prices)
	//We will calculate time based on seconds. 40 minute day/night cycle, so 2400 seconds, 24 hours in a day, etc.
	float currentTime; //int tenths
	float savedTimeOffset;

}; //CObjectManager