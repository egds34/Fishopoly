#include "pigObject.h"

#include "ComponentIncludes.h"

pigObject::pigObject(const Vector2& v) : CObject(TEST_SPRITE, v)
{
}

void pigObject::move()
{
	m_fRoll -= 0.25f * XM_2PI * m_pStepTimer->GetElapsedSeconds();  //rotate at 1/8 RPS
}