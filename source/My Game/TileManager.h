#pragma once

#include <algorithm> // for std::copy
#include <vector>
#include <random> //gaussian distribution

using namespace std;

#include "Common.h"
#include "Sprite.h"
#include "GameDefines.h"
#include "Renderer.h"
#include "Bezier.h"

#include <Random.h>

//Tile manager will handle the generation of terrain as well as provide chunk images depending on the location on the PC.

class TileManager : public CCommon
{
private:
	//this vector will hold the boundries on where to begin drawing the land downwards as well as hold the bounding line for fish/hook
	vector<int> border; //this will follow a pyramid type of scheme. the further you are from x = 0, the deeper it gets.
	vector<int> backgroundBorder; //this will be pretty random (put can be redone with a seed)

	CSpriteDesc3D* forwardChunk;
	CSpriteDesc3D* currentChunk;
	CSpriteDesc3D* backwardChunk;
	CSpriteDesc3D* fill;

	CRandom linearGenerator;

	default_random_engine generator;
	int currChunk = 22;
	int density;
	int quality = 2; //the lower the better

	Bezier bezierCurve;

	CSpriteDesc3D* drawChunk(int start, int end, int spriteIndex, vector<int>& pointList); //this will generate an image that encompasses all the points in the passed vector. this may be changed if i wind up labeling chunks per 1000 units
	vector<int> connectJaggedTerrain(vector<double> input); //this will connect all points created
	vector<int> connectSmoothTerrain(vector<double> input);

	double GetRandomSizeOffset(double mean, double deviation, double min, double max);
	void generateFill();
	void setPosition();

public:
	//generate terrain based on seed. this will populate the border variable
	TileManager(int seed, int density);
	void generateTerrain();

	//this will overwrite 1 of 3 terrain images (the one that is freed) with the current terrain image
	bool setChunk(int chunk);
	bool testCollision(Vector3 pos);

	//accessors for once!
	CSpriteDesc3D* getForwardChunk();
	CSpriteDesc3D* getCurrentChunk();
	CSpriteDesc3D* getBackwardChunk();
	CSpriteDesc3D* getFill();
};
