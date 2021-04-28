/// \file Game.h
/// \brief Interface for the game class CGame.

#pragma once

#include <WindowDesc.h>
//#inlcude <Random.h>

#include "Component.h"
#include "Common.h"
#include "ObjectManager.h"
#include "TileManager.h"
#include "Settings.h"

/// \brief The game class.

class CGame :
	public CWindowDesc,
	public CComponent,
	public CSettings,
	public CCommon {
private:
	bool m_bDrawFrameRate = false; ///< Draw the frame rate.
	bool isPaused = false;
	bool isDebug = false;
	bool isFishing = false;
	bool menuOpen = false;
	bool dialogOpen = false;
	bool moving_boat = false;
	int numFish = 10000;
	float m_fFrameTimer = 0.0f; 
	CObject* boat = nullptr;
	CObject* penguin = nullptr;
	CObject* fish = nullptr;

	CRandom worldGenerator;

	void BeginGame(); ///< Begin playing the game.
	void KeyboardHandler(); ///< The keyboard handler.
	void RenderFrame(); ///< Render an animation frame.
	void DrawFrameRateText(); ///< Draw frame rate text to screen.
	void CreateObjects(); ///< Create game objects.
	void CreateMenu();
	void resetPC();
	void CGame::FollowCamera();

public:
	~CGame(); ///< Destructor.

	void ShootBait(); ///< Shoot a bait to catch a fish

	void Initialize(); ///< Initialize the game.
	void ProcessFrame(); ///< Process an animation frame.
	void Release(); ///< Release the renderer.
}; //CGame
