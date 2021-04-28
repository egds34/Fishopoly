/// \file Renderer.cpp
/// \brief Code for the renderer class CRenderer.

#include "Renderer.h"
#include "ComponentIncludes.h"

#include "Abort.h"

CRenderer::CRenderer() :
	CSpriteRenderer(Unbatched3D) {
} //constructor

/// Load the specific images needed for this game.
/// This is where eSpriteType values from GameDefines.h get
/// tied to the names of sprite tags in gamesettings.xml. Those
/// sprite tags contain the name of the corresponding image file.
/// If the image tag or the image file are missing, then
/// the game should abort from deeper in the Engine code,
/// leaving you with a dialog box that tells you what
/// went wrong.

void CRenderer::LoadImages() {
	BeginResourceUpload();

	Load(START_PAGE1, "StartPage1");
	Load(START_PAGE2, "StartPage2");
	Load(START_PAGE3, "StartPage3");
	Load(START_PAGE4, "StartPage4");

	Load(CREDITS, "CREDITS");
	Load(SETTINGS, "SETTINGS");
	Load(CLICK_TO_START, "CLICK_TO_START");

	Load(ISLAND_SPRITE, "island");
	Load(DOCK_SPRITE, "dockFront");
	Load(DOCK_BACK, "dockBack");
	Load(CONNECTING_DOCK_SPRITE, "connectingDock");
	Load(CONNECTING_DOCK_3D_SPRITE, "connectingDock3D");

	Load(SUN_SPRITE, "sun");
	Load(FULL_MOON_SPRITE, "fullMoon");

	Load(BASE_SKY, "baseSky1");
	Load(BASE_SKY_YELLOW, "baseSky2");
	Load(BASE_SKY3, "baseSky3");
	Load(BASE_SKY4, "baseSky4");
	Load(SKY_HUE, "skyhue");
	Load(NIGHT_OVERLAY, "nightOverlay");
	Load(FOREGROUND, "foreground");

	Load(HOOK_SPRITE, "hook");
	Load(UNLOADED_FISH_SPRITE, "unloadedFishSprite");

	Load(PENGUIN_STOP_SPRITE, "penguinStatic");
	Load(PENGUIN_LEFT_SPRITE, "penguinLeft");
	Load(PENGUIN_RIGHT_SPRITE, "penguinRight");
	Load(PENGUIN_FISHING_SPRITE, "penguinFishing");

	Load(INVENTORY_MENU, "inventoryMenu");
	Load(BREEDING_MENU, "breedingMenu");
	Load(GEAR_MENU, "gearMenu");

	Load(OCEAN_BACKDROP, "ocean");
	Load(OCEAN_BACKDROP_YELLOW, "oceanYellow");
	Load(NIGHT_SHADE, "nightShadow");

	Load(UNLOADED_BOAT, "whiteline");
	Load(BOAT1, "boat1");
	Load(BOAT2, "boat2");
	Load(BOAT3, "boat3");

	//for HUD
	Load(NUMBER_0, "number0");
	Load(NUMBER_1, "number1");
	Load(NUMBER_2, "number2");
	Load(NUMBER_3, "number3");
	Load(NUMBER_4, "number4");
	Load(NUMBER_5, "number5");
	Load(NUMBER_6, "number6");
	Load(NUMBER_7, "number7");
	Load(NUMBER_8, "number8");
	Load(NUMBER_9, "number9");

	//for dialog
	Load(LETTER_0, "letter0");
	Load(LETTER_1, "letter1");
	Load(LETTER_2, "letter2");
	Load(LETTER_3, "letter3");
	Load(LETTER_4, "letter4");
	Load(LETTER_5, "letter5");
	Load(LETTER_6, "letter6");
	Load(LETTER_7, "letter7");
	Load(LETTER_8, "letter8");
	Load(LETTER_9, "letter9");

	Load(LETTER_A, "letterA");
	Load(LETTER_B, "letterB");
	Load(LETTER_C, "letterC");
	Load(LETTER_D, "letterD");
	Load(LETTER_E, "letterE");
	Load(LETTER_F, "letterF");
	Load(LETTER_G, "letterG");
	Load(LETTER_H, "letterH");
	Load(LETTER_I, "letterI");
	Load(LETTER_J, "letterJ");
	Load(LETTER_K, "letterK");
	Load(LETTER_L, "letterL");
	Load(LETTER_M, "letterM");
	Load(LETTER_N, "letterN");
	Load(LETTER_O, "letterO");
	Load(LETTER_P, "letterP");
	Load(LETTER_Q, "letterQ");
	Load(LETTER_R, "letterR");
	Load(LETTER_S, "letterS");
	Load(LETTER_T, "letterT");
	Load(LETTER_U, "letterU");
	Load(LETTER_V, "letterV");
	Load(LETTER_W, "letterW");
	Load(LETTER_X, "letterX");
	Load(LETTER_Y, "letterY");
	Load(LETTER_Z, "letterS");

	Load(LETTER_COLON, "letterColon");
	Load(LETTER_COMMA, "letterComma");
	Load(LETTER_COMMA_NORMAL, "letterCommaNormal");
	Load(LETTER_QUESTION, "letterQuestion");

	Load(CURRENCY_BAR, "currencyBar");
	Load(TIME_BAR, "timeBar");

	Load(WHITE_LINE, "whiteline");

	Load(DIALOG_BOX, "dialogBox");
	Load(CONFIRM_BUTTON, "confirmButton");
	Load(CANCEL_BUTTON, "cancelButton");
	Load(CONFIRM_BUTTON_HIGHLIGHTED, "confirmButtonHighlighted");
	Load(CANCEL_BUTTON_HIGHLIGHTED, "cancelButtonHighlighted");

	Load(HOVER_INVENTORY_BACKGROUND, "inventoryFishHoverBackground");
	Load(SELECT_INVENTORY_BACKGROUND, "inventoryFishSelectBackground");
	Load(NORMAL_INVENTORY_BACKGROUND, "inventoryFishNormalBackground");
	Load(SELECT_HOVER_INVENTORY_BACKGROUND, "inventoryFishSelectHoverBackground");
	
	Load(HOVER_ITEM_BACKGROUND, "gearItemHover");
	Load(SELECT_ITEM_BACKGROUND, "gearItemSelectedNormal");
	Load(NORMAL_ITEM_BACKGROUND, "gearItemNormal");
	Load(SELECT_HOVER_ITEM_BACKGROUND, "gearItemSelectedHover");

	Load(BUTTON_SELL_NORMAL, "inventorySellButtonNormal");
	Load(BUTTON_SELL_HIGHLIGHTED, "inventorySellButtonHover");
	Load(BUTTON_SELL_GRAY, "inventorySellButtonGray");

	Load(BUTTON_INFO_NORMAL, "inventoryInfoButtonNormal");
	Load(BUTTON_INFO_HIGHLIGHTED, "inventoryInfoButtonHover");
	Load(BUTTON_INFO_GRAY, "inventoryInfoButtonGray");

	Load(BUTTON_BREED_NORMAL, "inventoryBreedButtonNormal");
	Load(BUTTON_BREED_HIGHLIGHTED, "inventoryBreedButtonHover");
	Load(BUTTON_BREED_GRAY, "inventoryBreedButtonGray");

	Load(BUTTON_RELEASE_NORMAL, "inventoryLetgoButtonNormal");
	Load(BUTTON_RELEASE_HIGHLIGHTED, "inventoryLetgoButtonHover");
	Load(BUTTON_RELEASE_GRAY, "inventoryLetgoButtonGray");

	Load(BUTTON_BUY_NORMAL, "buyButtonNormal");
	Load(BUTTON_BUY_HIGHLIGHTED, "buyButtonHover");
	Load(BUTTON_BUY_GRAY, "buyButtonGray");

	Load(BUTTON_SELECT_NORMAL, "selectButtonNormal");
	Load(BUTTON_SELECT_HIGHLIGHTED, "selectButtonHover");
	Load(BUTTON_SELECT_GRAY, "selectButtonGray");

	Load(ICON_POLE_1, "poleIcon1");
	Load(ICON_POLE_2, "poleIcon2");
	Load(ICON_POLE_3, "poleIcon3");
	Load(ICON_POLE_4, "poleIcon4");
	Load(ICON_POLE_5, "poleIcon5");
	Load(ICON_POLE_6, "poleIcon6");

	Load(ICON_BOAT_1, "boatIcon1");
	Load(ICON_BOAT_2, "boatIcon2");
	Load(ICON_BOAT_3, "boatIcon3");

	Load(ICON_WEIGHT_1, "weightIcon1");
	Load(ICON_WEIGHT_2, "weightIcon2");
	Load(ICON_WEIGHT_3, "weightIcon3");

	Load(ICON_LOCK, "lock");

	EndResourceUpload();
} //LoadImages

void CRenderer::LoadImages(int index, bool upload)
{
	BeginResourceUpload();
	if (upload) Load(index, "fishSprite");
	else Load(index, "terrain");
	EndResourceUpload();
}

void CRenderer::LoadFill()
{
	BeginResourceUpload();
	Load(TERRAIN_FILL, "terrainFill");
	EndResourceUpload();
}