#pragma once
#include "Object.h"
class TimeBarObject :
	public CObject
{
private:
	int time = 0;
	list<CSpriteDesc3D*> numberDisplay;
public:
	TimeBarObject(Vector3& v);
	void move();
	void setTime(float time);
	list<CSpriteDesc3D*> getDisplayList();
};
