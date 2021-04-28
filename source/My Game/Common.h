/// \file Common.h
/// \brief Interface for the class CCommon.

#pragma once

#include "SndList.h"
#include "ParticleEngine.h"
#include "GameDefines.h"
//#include "TileManager.h"

#include <Magick++.h>

//forward declarations to make the compiler less stroppy

class CObjectManager;
class CRenderer;
class TileManager;
class CObject;
class MenuObject;

#define GetWidth(n) m_pRenderer->GetWidth(n) ///< Shorthand for sprite width.
#define GetHeight(n) m_pRenderer->GetHeight(n) ///< Shorthand for sprite height.

/// \brief The common variables class.
///
/// CCommon is a singleton class that encapsulates
/// things that are common to different game components,
/// including game state variables.
/// Making it a singleton class means
/// that we can avoid passing its member variables
/// around as parameters, which makes the code
/// minisculely faster, and more importantly, reduces
/// function clutter.

class CCommon {
protected:
	static CRenderer* m_pRenderer; ///< Pointer to the renderer.
	static CObjectManager* m_pObjectManager; ///< Pointer to the object manager.
	static TileManager* m_pTileManager;

	static eSoundType m_eDownSnd; ///< Key down sound.
	static eSoundType m_eUpSnd; ///< Key up sound.

	static float m_fWorldScale; ///< World scale.
	static float m_fChunkSize; ///< chunk size. we only care about the x axis as the chunk will extend the full comlumn length.
	static unsigned m_nNumChunks; ///< Number of cells.
	static float m_fWorldWidth; ///< World width.
	static int worldStartChunk;
	static int worldEndChunk; //used to checking when to wrap. this changes as you upgrade your boat ^.^

	//test, replace with boat object
	static CObject* boat;

	static CObject* PC;
	static MenuObject* menu;

	Magick::Image newImage;
	Magick::Image terrainImage;

	static vector<bool> freeIndices;
public:
	int getNextFishSpriteIndex();
	void releaseSpriteIndex(int index);
	float Wrap(float x); ///< Wrap horizontal distance.
}; //CCommon
