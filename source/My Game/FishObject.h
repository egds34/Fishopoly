#pragma once

#include <vector>
#include <stdlib.h>
#include <Random.h>
#include <random> //gaussian distribution
#include <math.h> //common function arithmetic
#include <sstream> //stringstream

#include "Bezier.h"
#include "Object.h"
#include "GameDefines.h"

/// <summary>
/// fish rules
/// fish increase size the deeper they are
/// fish increase in size the for large values of abs(x), which is how far away they are from the main starting point
/// fish can have s set amount of colours and at lease one shade of the primary
/// hereditary traits for orientation of fish
/// hereditary traits for solid, spots or lines with a secondary or tertiary color
/// heriditary trait for feeding time
/// static lifespan of random parent + or - a random offset
/// save for later static pubescent period of random parent +- a random offset
/// static birth rest period (females) of random parent +- a random offset
/// static depth of random parent +- an offest
/// static wieght of random parent +- an offset
/// static breed time
/// static swimming velocity
/// static depth
///
/// sprite uses seed from a new rng variable
/// parents of the same species should have the same sprite just altered in size!!! - smallest is 19x19? largest is 200x200
///
/// birthday and birth place and species name are independant of the seed, though a recommended species name will be pulled out of nowhere
///
/// ocean should be a parameter because fish generated during world generation should be bound by constrictions of the ocean (size)
/// start with maybe 32 fish per ocean, each fish will have a
/// </summary>

class FishObject :
	public CObject
{
private:
	//think of these seeds as chromosomes

	int price = 0; //this should be a string in the future.

	int size = 10;
	int spriteIndex;
	int prevDirection;
	//int feedingTime;

	bool rotateLeft = false;
	bool isResisting = true;
	float originalSpeed;
	float acc = 0.0;
	float resistTimer = 0.0;

	bool setVec = true;

	bool moveUp = true;
	float step;
	float beginningY = 0.0f; 
	//sprite generation helper variables
	std::vector<std::vector<int>> sprite2D;
	std::vector<std::vector<int>> tempSprite2D;

	CRandom linearGenerator;
	std::default_random_engine generator;

	//shaping variables
	double  bodyStartX;
	double  bodyStartY;
	double  bodyEndX;
	double  bodyEndY;

	double  bodyMaximalY; double  bodyMaximalX;
	double  bodyMinimalX; double  bodyMinimalY;
	double  bodyShapePoint3X; double  bodyShapePoint3Y;

	double tailTopStartX, tailTopStartY;
	double tailBotStartX, tailBotStartY;
	double tailMaximalX, tailMaximalY;
	double tailMinimalX, tailMinimalY;
	double tailEndX, tailEndY;

	//coloring variables
	int r, g, b, r1, g1, b1;

	//currency variable
	float curr;

	Bezier bezierCurve;

public:
	FishObject(const Vector3& v, int level, int worldSeed); //level is the ocean
	
	int getPrice(); //get fish's price
	int GenerateSprite(); //use with world gen
	int feedingTime;
private:

	//int GenerateSprite(int momSpriteSeed, int dadSpriteSeed); //use when breeding
	void GenerateProperties(int momPropertySeed, int dadPropertySeed); //this is a TODO, probs for the final milestone
	void GenerateCreature();

	int GetRandomSizeOffset(double mean, double deviation, int size, double min, double max);

	void move();

	void CreateImage(int shape);

	constexpr int pixelArraySize();

	//functions to get prices of fishes
	int normal_dist(int i);
	string RGBtoHex();
};
