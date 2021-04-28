/// \file Object.h
/// \brief Interface for the game object class CObject.

#pragma once

#include "GameDefines.h"
#include "Renderer.h"
#include "Common.h"
#include "Component.h"
#include "ComponentIncludes.h"
#include "SpriteDesc.h"

/// \brief The game object.
///
/// CObject is the abstract representation of an object.

class CObject :
	public CCommon,
	public CComponent,
	public CSpriteDesc3D
{
	friend class CObjectManager; ///< The object manager needs access to manage objects.

private:
	bool m_bDead = false; ///< Is dead or not.
	//pass in an int 0-3 to see if the fish spawns at the given time.
protected:
	CParticleEngine3D* m_pParticleEngine = nullptr; ///< Pointer to a particle engine.
	float unit = 5.0;
	float m_fFrameTimer = 0.0f; ///< Last time the frame was changed.
	float m_fFrameInterval = 0.1f;
	float offset = 0;

	Vector3 m_vVelocity = Vector3::Zero; ///< Velocity.
	

public:
	//testing
	int seed;
	bool isBoarded = false;

	int boat; //to be used by boat objects..... maybe that shouldve been its own class.

	Vector3 originalPoint = Vector3::Zero; //this will be used to release fish. x will be generally random, but y needs to be constant (z too obviously).
	//make accessors when you feel like it i guess, lazy bum (to Christy, from Christy)
	int direction;
	int worldIndex; //this will keep track of when objects are bound to a world. this will help when wrapping our dynamic worlds
	float originalYScale;
	float originalXScale;
	float m_fSpeed = 0; ///< Speed.
	bool isHooked = false;
	bool isCaught = false;
	Vector3 anchorPoint = Vector3::Zero;
	int r, g, b; //fish's color

	CObject(eSpriteType t, const Vector3& p); ///< Constructor.
	const Vector3& GetPos();
	void SetSpeed(float speed); //
	virtual void ProduceTestPNG();
	virtual int GenerateSprite();
	virtual void move(); ///< Move object.
	virtual list<CSpriteDesc3D*> getDisplayList();
	void kill(); ///< Kill me.
	bool IsDead(); ///< Query whether dead.
	int getCurrentChunk();

	//double BoatUpDown(int param); //param = from 0 to 359
}; //CObject