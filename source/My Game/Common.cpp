/// \file Common.cpp
/// \brief Code for the class CCommon.
///
/// This file contains declarations and initial values
/// for CCommon's static member variables.

#include "Common.h"

/// Include renderer and object manager
CRenderer* CCommon::m_pRenderer = nullptr;
CObjectManager* CCommon::m_pObjectManager = nullptr;
TileManager* CCommon::m_pTileManager = nullptr;

CObject* CCommon::PC = nullptr;
MenuObject* CCommon::menu = nullptr;

// Add variables to set dimensions of background
int  CCommon::worldStartChunk = 0;
int CCommon::worldEndChunk = 0; //used to checking when to wrap. this changes as you upgrade your boat ^.^

//test, replace with boat object
CObject* CCommon::boat = nullptr;

float CCommon::m_fWorldScale = 2.0f;

float CCommon::m_fWorldWidth = 90000.0f;
float CCommon::m_fChunkSize = 2000.0f; //this absolutely needs to be constant. the screen size changes automatically

unsigned CCommon::m_nNumChunks = 11;

vector<bool> CCommon::freeIndices(512, true);
/// Wrap a horizontal distance to plus or minus half the world width.
/// This will be used to normalize the distances from various objects to the BAIT.
/// \param x Horizontal distance.
/// \return Horizontal distance normalized to half the world width.

int CCommon::getNextFishSpriteIndex()
{
	for (int i = 0; i < 512; ++i)
	{
		if (freeIndices[i] == true)
		{
			freeIndices[i] = false;
			return i + NUM_SPRITES;
		}
	}
	return -1;
}

void CCommon::releaseSpriteIndex(int index)
{
	freeIndices[index] = true;
}

// TODO: modify the below for bait
float CCommon::Wrap(float x) {
	const float wdiv2 = m_fWorldWidth / 2;
	return x - wdiv2 * (int)ceil(x / wdiv2);
} //Wrap