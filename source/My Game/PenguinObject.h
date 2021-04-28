#pragma once

#include "Object.h"

class PenguinObject : public CObject
{
private:

public:
	PenguinObject(const Vector2& p, eSpriteType t); ///< Constructor.

	virtual void Move(); ///< Move object.
};
