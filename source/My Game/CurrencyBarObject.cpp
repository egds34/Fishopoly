#include "CurrencyBarObject.h"
#include "FishObject.h"

#include <math.h>

CurrencyBarObject::CurrencyBarObject(Vector3& v) : CObject(CURRENCY_BAR, v)
{
}

void CurrencyBarObject::move()
{
	if (round(currentAmount) != round(setAmount))
	{
		setCurrency(currentAmount + increment);
	}
	else
	{
		increment = 0;
		currentAmount = setAmount; //removing tiny floating point decimals
	}
	if (PC->m_vPos.y < 0.0)
	{
		m_vPos.x = PC->m_vPos.x - 305;
	}
	//it was at this point that i could have inherited a general HUD object so lets make that a TODO
	else m_vPos = Vector3(PC->m_vPos.x - 305, PC->m_vPos.y + 209, 1000.0f);
	float currX = -54.0f;
	for (auto& i : numberDisplay)
	{
		if (i->m_nSpriteIndex != LETTER_COMMA) currX += 5;

		i->m_vPos = Vector3(m_vPos.x + currX, m_vPos.y, m_vPos.z);
		if (i->m_nSpriteIndex == LETTER_COMMA) currX += 5.0f;
		else currX += 10.0f;

	}
}

void CurrencyBarObject::setCurrency(float currency)
{
	numberDisplay.clear();
	currentAmount = currency;

	string sCurrency = to_string((int)round(currency));

	float currX = -46.0f;
	int count = 0;

	for (int i = 0; i < (9 - sCurrency.length()); ++i) //place 0 in front of number
	{
		CSpriteDesc3D* p = new CSpriteDesc3D();
		p->m_vPos = Vector3(m_vPos.x + currX, m_vPos.y, m_vPos.z);
		p->m_nSpriteIndex = NUMBER_0;
		numberDisplay.push_back(p);
		count += 1;
		currX += 15.0f;
		if ((count == 3) || (count == 6))
		{
			CSpriteDesc3D* p = new CSpriteDesc3D();
			p->m_vPos = Vector3(m_vPos.x + currX, m_vPos.y, m_vPos.z);
			p->m_nSpriteIndex = LETTER_COMMA;
			numberDisplay.push_back(p);
			currX += 15.0f;
		}
	}
	for (auto i : sCurrency)
	{
		CSpriteDesc3D* p = new CSpriteDesc3D();
		p->m_vPos = Vector3(m_vPos.x + currX, m_vPos.y, m_vPos.z);
		switch (i)
		{
		case '0':
			p->m_nSpriteIndex = NUMBER_0;
			break;
		case '1':
			p->m_nSpriteIndex = NUMBER_1;
			break;
		case '2':
			p->m_nSpriteIndex = NUMBER_2;
			break;
		case '3':
			p->m_nSpriteIndex = NUMBER_3;
			break;
		case '4':
			p->m_nSpriteIndex = NUMBER_4;
			break;
		case '5':
			p->m_nSpriteIndex = NUMBER_5;
			break;
		case '6':
			p->m_nSpriteIndex = NUMBER_6;
			break;
		case '7':
			p->m_nSpriteIndex = NUMBER_7;
			break;
		case '8':
			p->m_nSpriteIndex = NUMBER_8;
			break;
		case '9':
			p->m_nSpriteIndex = NUMBER_9;
			break;
		}
		count += 1;
		numberDisplay.push_back(p);
		currX += 15.0f;
		if ((count == 3) || (count == 6))
		{
			CSpriteDesc3D* p = new CSpriteDesc3D();
			p->m_vPos = Vector3(m_vPos.x + currX, m_vPos.y, m_vPos.z);
			p->m_nSpriteIndex = LETTER_COMMA;
			numberDisplay.push_back(p);
			currX += 10.0f;
		}
	}
}

int CurrencyBarObject::getCurrency()
{
	return setAmount;
}

int CurrencyBarObject::caughtFish() 
{
	//call the getPrice function
	//FishObject* fish;
	//setAmount = fish->getPrice(fish);

	//return the price of fish
	return setAmount;
}

bool CurrencyBarObject::addCurrency(int amount)
{
	//call the price of fish
	setAmount = caughtFish();

	if (setAmount + amount > 999999999) return false;
	if (setAmount + amount < 0) return false;

	float numFrames = 60;

	setAmount += amount;
	increment = (setAmount - currentAmount) / numFrames;
	return true;
}

list<CSpriteDesc3D*> CurrencyBarObject::getDisplayList()
{
	return numberDisplay;
}
