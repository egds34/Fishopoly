#include "TimeBarObject.h"

TimeBarObject::TimeBarObject(Vector3& v) : CObject(TIME_BAR, v)
{
}

void TimeBarObject::move()
{
	if (PC->m_vPos.y < 0.0)
	{
		m_vPos.x = PC->m_vPos.x - 338;
	}
	//it was at this point that i could have inherited a general HUD object so lets make that a TODO
	else m_vPos = Vector3(PC->m_vPos.x - 338, PC->m_vPos.y + 182, 1000.0f);
	float currX = -14.0f;
	for (auto& i : numberDisplay)
	{
		i->m_vPos = Vector3(m_vPos.x + currX, m_vPos.y, m_vPos.z);
		currX += 15.0f;
	}
}

void TimeBarObject::setTime(float time)
{
	numberDisplay.clear();

	float minutes = ((fmod(time, 100)) / 100.0) * 60.0;
	float hours = time / 100;
	string sMinutes = to_string((int)minutes);
	string sHours = to_string((int)hours);

	float currX = -14.0f;
	int count = 0;
	string s = sHours;
	for (int j = 0; j < 2; ++j)
	{
		for (int i = 0; i < (2 - s.length()); ++i)
		{
			CSpriteDesc3D* p = new CSpriteDesc3D();
			p->m_vPos = Vector3(m_vPos.x + currX, m_vPos.y, m_vPos.z);
			p->m_nSpriteIndex = NUMBER_0;
			numberDisplay.push_back(p);
			count += 1;
			currX += 15.0f;
			if (count == 2)
			{
				CSpriteDesc3D* p = new CSpriteDesc3D();
				p->m_vPos = Vector3(m_vPos.x + currX, m_vPos.y, m_vPos.z);
				p->m_nSpriteIndex = LETTER_COLON;
				numberDisplay.push_back(p);
				currX += 15.0f;
			}
		}
		for (auto i : s)
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
			if (count == 2)
			{
				CSpriteDesc3D* p = new CSpriteDesc3D();
				p->m_vPos = Vector3(m_vPos.x + currX, m_vPos.y, m_vPos.z);
				p->m_nSpriteIndex = LETTER_COLON;
				numberDisplay.push_back(p);
				currX += 15.0f;
			}
		}
		s = sMinutes;
	}
	
}

list<CSpriteDesc3D*> TimeBarObject::getDisplayList()
{
	return numberDisplay;
}