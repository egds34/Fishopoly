/// \file SndList.h
/// \brief Enumerated type for sounds.

#pragma once

#include "Sound.h"

/// \brief Game sound enumerated type. 
///
/// These are the sounds used in actual gameplay. 
/// The sounds must be listed here in the same order that
/// they are in the sound settings XML file.

enum eSoundType{ 
  FISH_UNDER_WATER, MONEY, OCEAN1_THEME, UNDERWATER, WAVES, BLOP, WALK1, WALK2, HOOK_IN_WATER, CATCH,
  SELECT, MENU_OPEN, MENU_CLOSE
}; //eSoundType