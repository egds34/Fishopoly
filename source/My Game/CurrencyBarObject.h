#pragma once
#include "Object.h"

class CurrencyBarObject :
	public CObject
{
private:
	float currentAmount = 0.0;
	float setAmount = 0.0; //this is used as a check when animating displayed currency
	float increment; //this is used for animating the currency when we add or take away money
	float currencyOffset;
	list<CSpriteDesc3D*> numberDisplay;
public:
	CurrencyBarObject(Vector3& v);
	void move();
	void setCurrency(float currency);
	int getCurrency();
	int caughtFish();
	bool addCurrency(int amount); //returns false if max money is reached;
	list<CSpriteDesc3D*> getDisplayList();
};
