#include "HookObject.h"

HookObject::HookObject(const Vector3& v, bool underWater) : CObject(HOOK_SPRITE, v)
{
	anchorPoint = v;
	isInWater = underWater;

	switch (m_pObjectManager->getPoleType()->m_nSpriteIndex)
	{
	case ICON_POLE_1:
		minY = -1000;
		break;
	case ICON_POLE_2:
		minY = -2000;
		break;
	case ICON_POLE_3:
		minY = -3000;
		break;
	case ICON_POLE_4:
		minY = -4000;
		break;
	case ICON_POLE_5:
		minY = -5000;
		break;
	case ICON_POLE_6:
		minY = -10000;
		break;
	}

	switch (m_pObjectManager->getWeightType()->m_nSpriteIndex)
	{
	case ICON_WEIGHT_1:
		speedModifier = 1.5;
		break;
	case ICON_WEIGHT_2:
		speedModifier = 2.0;
		break;
	case ICON_WEIGHT_3:
		speedModifier = 3.0;
		break;
	}
}

void HookObject::move()
{
	//TODO work on rolling the hook
	POINT p, q, r;
	p.x = 0; p.y = 0;
	ScreenToClient(m_Hwnd, &p);
	GetCursorPos(&q);
	r.x = (p.x + q.x) - (1280 / 2);
	r.y = p.y + q.y;

	const float t = m_pStepTimer->GetElapsedSeconds();

	if (isInWater == false)
	{
		if (m_vVelocity.x == 0) m_vVelocity.x = t * r.x; //this should only be set one time

		if (m_vVelocity.y == 0) m_vVelocity.y = 8.0f;
		m_vVelocity -= 20.0f * t * Vector3::UnitY;
		m_vPos += 64.0f * t * m_vVelocity;
		if (m_vPos.y <= -145.0f)
		{
			m_pAudio->play(HOOK_IN_WATER);
			m_pAudio->stop(WAVES);
			m_pAudio->loop(UNDERWATER);
			isInWater = true;
		}
	}
	else
	{
		if (m_fSpeed < 0.0f)
		{
			m_vVelocity = Vector3::Zero;

			const float t = m_pStepTimer->GetElapsedSeconds();
			float delta_x = m_vPos.x - anchorPoint.x;
			float delta_y = m_vPos.y - anchorPoint.y;

			float distance = sqrt((delta_x * delta_x) + (delta_y * delta_y));
			float dvx = delta_x * (m_fSpeed) / distance; //-5 should be a common variable based on the fishing pole!!!!!!!!!!!!!!!!!!!!!!
			float dvy = delta_y * (m_fSpeed) / distance;
			delta_x = dvx - m_vVelocity.x;
			delta_y = dvy - m_vVelocity.y;
			float diffSize = sqrt((delta_x * delta_x) + (delta_y * delta_y));
			float ax = 0.0, ay = 0.0;
			if (diffSize != 0.0f)
			{
				ax = 50 * delta_x / diffSize;
				ay = 50 * delta_y / diffSize;
			}
			m_vVelocity.x += 64.0f * ax * t; // t is the time that passed since the last frame
			m_vVelocity.y += 64.0f * ay * t; // t is the time that passed since the last frame

			m_vPos += m_vVelocity;
		}
		else
		{
			m_vPos.y -= m_fSpeed * unit * speedModifier;

			//these are for those people with two monitors who think they can get a little extra speed from the hook in the water.
			if (r.x > (1280 / 2)) r.x = (1280 / 2);
			else if (r.x < -(1280 / 2)) r.x = -(1280 / 2);

			m_vVelocity.x = (m_fSpeed * r.x) / 500;
			m_vPos.x += m_fSpeed * unit * m_vVelocity.x;
		}
		if (m_vPos.y >= 0)
		{
			m_vPos.y = 0;
			PC->kill();
		}
		if ((m_vPos.y >= -145) && (playOutSound))
		{
			m_pAudio->play(HOOK_IN_WATER, 2.0);
			m_pAudio->stop(UNDERWATER);
			m_pAudio->loop(WAVES);
			playOutSound = false;
		}
		if (m_vPos.y < minY)
		{
			printf("true");
			m_fSpeed = -10;
			speedModifier = 1;
		}
	}
}