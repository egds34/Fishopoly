#pragma once
#include "ObjectManager.h"
#include "Object.h"

class HookObject :
	public CWindowDesc,
	public CObject
{
private:
	bool playOutSound = true;
	bool setVec;
	bool isInWater;
	int minY = 0;
	float speedModifier = 1; //this is changed if the user buys a weight.
public:
	HookObject(const Vector3& v, bool underWater);
	void move();
};
