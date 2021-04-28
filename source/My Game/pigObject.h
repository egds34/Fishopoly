#pragma once
#include "Object.h"

class pigObject : public CObject
{
public:
	pigObject(const Vector2& v);
	void move();
};
