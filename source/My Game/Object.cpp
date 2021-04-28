/// \file Object.cpp
/// \brief Code for the game object class CObject.

#include "Object.h"
#include "ComponentIncludes.h"
#include <math.h> //sin function

/// \param t Type of sprite.
/// \param p Initial position of object.


CObject::CObject(eSpriteType t, const Vector3& p) {
	m_nSpriteIndex = t;
	m_vPos = p;
	originalXScale = m_fXScale;
	originalYScale = m_fYScale;
} //constructor

const Vector3& CObject::GetPos() {
	return m_vPos;
} //GetPos

void CObject::SetSpeed(float speed) {
	m_fSpeed = speed;
} //SetVelocity

void CObject::ProduceTestPNG()
{
}

int CObject::GenerateSprite()
{
	return -1;
}

void CObject::move() {
	//m_fRoll += 0.125f * XM_2PI * m_pStepTimer->GetElapsedSeconds();  //rotate at 1/8 RPS

	//animate multiframe sprite
	const size_t nFrameCount = m_pRenderer->GetNumFrames(m_nSpriteIndex);
	if (!isBoarded)
	{
		if (nFrameCount > 1 && m_pStepTimer->GetTotalSeconds() > m_fFrameTimer + 0.15) {
			m_fFrameTimer = m_pStepTimer->GetTotalSeconds();
			m_nCurrentFrame = (m_nCurrentFrame + 1) % nFrameCount;

			if (((m_nSpriteIndex == PENGUIN_LEFT_SPRITE) || (m_nSpriteIndex == PENGUIN_RIGHT_SPRITE)) && (m_nCurrentFrame == 0))
			{
				m_pAudio->play(WALK2, 0.5);
			}
			else if (((m_nSpriteIndex == PENGUIN_LEFT_SPRITE) || (m_nSpriteIndex == PENGUIN_RIGHT_SPRITE)) && (m_nCurrentFrame % 2 == 0))
			{
				m_pAudio->play(WALK1, 0.5);
			}
		} //ifad
	}
	else (m_nCurrentFrame = 1);
	//movesprite appropriately, possible make this a switch statement TODO

	if (((m_nSpriteIndex == PENGUIN_LEFT_SPRITE)) && ((m_vPos.x - 1.0f) > -780) && !isBoarded)
		m_vPos.x -= m_fSpeed * unit;
	if (((m_nSpriteIndex == PENGUIN_RIGHT_SPRITE)) && ((m_vPos.x + 1.0f) < 780) && !isBoarded)
		m_vPos.x += m_fSpeed * unit;

	if (((m_nSpriteIndex == PENGUIN_LEFT_SPRITE)) && isBoarded)
		m_vPos.x -= m_fSpeed * 4 * unit;
	if (((m_nSpriteIndex == PENGUIN_RIGHT_SPRITE)) && isBoarded)
		m_vPos.x += m_fSpeed * 4 * unit;

	///if ((m_nSpriteIndex == PENGUIN_STOP_SPRITE))// && ((m_vPos.x + 1.0f) < 780))
		//m_vPos.y += m_fSpeed * unit;

	if ((m_nSpriteIndex == CONNECTING_DOCK_3D_SPRITE) && (PC->m_nSpriteIndex == PENGUIN_LEFT_SPRITE) && ((PC->m_vPos.x - 1.0f) > -780))
		m_vPos.x -= 0.03 * PC->m_fSpeed;
	if ((m_nSpriteIndex == CONNECTING_DOCK_3D_SPRITE) && (PC->m_nSpriteIndex == PENGUIN_RIGHT_SPRITE) && ((PC->m_vPos.x + 1.0f) < 780))
		m_vPos.x += 0.03 * PC->m_fSpeed;

	if ((PC->isBoarded) && (PC->m_nSpriteIndex == m_nSpriteIndex))
	{
		CCommon::boat->m_vPos.x = m_vPos.x;
		CCommon::boat->m_vPos.z = m_vPos.z - 1;

	}
} //move

list<CSpriteDesc3D*> CObject::getDisplayList()
{
	return list<CSpriteDesc3D*>();
}

/// Kill an object by marking its "is dead" flag. The object
/// will get deleted later at the appropriate time.

void CObject::kill() {
	m_bDead = true;
} //kill

/// Reader function for the "is dead" flag.
/// \return true if marked as being dead, that is, ready for disposal.

bool CObject::IsDead() {
	return m_bDead;
} //IsDead

int CObject::getCurrentChunk()
{
	int m_nResult;
	if (m_vPos.x >= 0)
		m_nResult = int(m_vPos.x + (m_fChunkSize / 2));
	else
		m_nResult = int(m_vPos.x - (m_fChunkSize / 2));

	//return (m_nResult / int(m_fChunkSize));

	return m_vPos.x;
}

//double BoatUpDown(int param)
//{
//	if (param < 359)
//	{
//		param++;
//	}
//	else if (param == 359)
//	{
//		param = 0;
//	}
//
//	double result;
//	result = sin(param * 3.14159265 / 180);
//	return result;
//}