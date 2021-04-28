/// \file GameDefines.h
/// \brief Game specific defines.

#pragma once

#include "Defines.h"

/// \brief Sprite type.
///
/// Note: NUM_SPRITES must be last.

enum eSpriteType {
	START_PAGE1, START_PAGE2, START_PAGE3, START_PAGE4,
	CREDITS, SETTINGS, CLICK_TO_START,
	PENGUIN_STOP_SPRITE, PENGUIN_LEFT_SPRITE, PENGUIN_RIGHT_SPRITE, PENGUIN_FISHING_SPRITE, 
	HOOK_SPRITE, WHITE_LINE,
	BACKGROUND_SPRITE, ISLAND_SPRITE, DOCK_SPRITE, DOCK_BACK, CONNECTING_DOCK_SPRITE, CONNECTING_DOCK_3D_SPRITE,
	BASE_SKY, BASE_SKY_YELLOW, SKY_HUE, NIGHT_OVERLAY,
	BASE_SKY2, BASE_SKY3, BASE_SKY4,
	OCEAN_BACKDROP, OCEAN_BACKDROP_YELLOW, NIGHT_SHADE, FOREGROUND,
	TERRAIN1, TERRAIN2, TERRAIN3, TERRAIN_FILL,
	SUN_SPRITE, NEW_MOON_SPRITE, FULL_MOON_SPRITE, WANING_GIBBOUS_SPRITE, WANING_CRESCENT_SPRITE, WAXING_CRESCENT_SPRITE,
	WAXING_GIBBOUS_SPRITE, FIRST_QUARTER_SPRITE, THIRD_QUARTER_SPRITE,
	INVENTORY_MENU, BREEDING_MENU, GEAR_MENU,
	ICON_BOAT_1, ICON_BOAT_2, ICON_BOAT_3,
	ICON_WEIGHT_1, ICON_WEIGHT_2, ICON_WEIGHT_3,
	ICON_POLE_1, ICON_POLE_2, ICON_POLE_3, ICON_POLE_4, ICON_POLE_5, ICON_POLE_6,
	ICON_LOCK,
	UNLOADED_BOAT, BOAT1, BOAT2, BOAT3, 
	UNLOADED_FISH_SPRITE,
	SELECT_HOVER_INVENTORY_BACKGROUND, HOVER_INVENTORY_BACKGROUND, SELECT_INVENTORY_BACKGROUND, NORMAL_INVENTORY_BACKGROUND,
	SELECT_HOVER_ITEM_BACKGROUND, HOVER_ITEM_BACKGROUND, SELECT_ITEM_BACKGROUND, NORMAL_ITEM_BACKGROUND,
	BUTTON_SELL_NORMAL, BUTTON_SELL_HIGHLIGHTED, BUTTON_SELL_GRAY,
	BUTTON_INFO_NORMAL, BUTTON_INFO_HIGHLIGHTED, BUTTON_INFO_GRAY,
	BUTTON_BREED_NORMAL, BUTTON_BREED_HIGHLIGHTED, BUTTON_BREED_GRAY,
	BUTTON_RELEASE_NORMAL, BUTTON_RELEASE_HIGHLIGHTED, BUTTON_RELEASE_GRAY,
	BUTTON_BUY_NORMAL, BUTTON_BUY_HIGHLIGHTED, BUTTON_BUY_GRAY,
	BUTTON_SELECT_NORMAL, BUTTON_SELECT_HIGHLIGHTED, BUTTON_SELECT_GRAY,
	DIALOG_BOX, CONFIRM_BUTTON, CANCEL_BUTTON, CONFIRM_BUTTON_HIGHLIGHTED, CANCEL_BUTTON_HIGHLIGHTED,
	NUMBER_0, NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9,
	LETTER_COLON, LETTER_COMMA, LETTER_QUESTION, LETTER_COMMA_NORMAL,
	LETTER_1, LETTER_2, LETTER_3, LETTER_4, LETTER_5, LETTER_6, LETTER_7, LETTER_8, LETTER_9, LETTER_0,
	LETTER_A, LETTER_B, LETTER_C, LETTER_D, LETTER_E, LETTER_F, LETTER_G, LETTER_H, LETTER_I, LETTER_J, LETTER_K, LETTER_L, LETTER_M,
	LETTER_N, LETTER_O, LETTER_P, LETTER_Q, LETTER_R, LETTER_S, LETTER_T, LETTER_U, LETTER_V, LETTER_W, LETTER_X, LETTER_Y, LETTER_Z, 
	CURRENCY_BAR, TIME_BAR,
	NUM_SPRITES //MUST BE LAST
}; //eSpriteType

enum dialogType {
	SELL_DIALOG, INFO_DIALOG, BREED_DIALOG, RELEASE_DIALOG, BUY_DIALOG, FAIL_DIALOG
};