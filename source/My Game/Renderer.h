/// \file Renderer.h
/// \brief Interface for the renderer class CRenderer.

#pragma once

#include "GameDefines.h"
#include "SpriteRenderer.h"

/// \brief The renderer.
///
/// CRenderer handles the game-specific rendering tasks, relying on
/// the base class to do all of the actual API-specific rendering.

class CRenderer : public CSpriteRenderer {
public:
	CRenderer(); ///< Constructor.

	void LoadImages(); ///< Load images.
	void LoadImages(int index, bool upload); //if the bool is true, then we set the image of the current index
	void LoadFill(); //if the bool is true, then we set the image of the current index
}; //CRenderer