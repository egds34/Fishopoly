/// \file Game.cpp
/// \brief Code for the game class CGame.

#include "Game.h"

#include "GameDefines.h"
#include "Renderer.h"
#include "ComponentIncludes.h"

//place in objectmanager.cpp.... debugging right now
//for the sake of time, generated fish are going to be simple and related to that image I sent you at the beginning of the semester
#include "FishObject.h"
#include "MenuObject.h"

/// Delete the object manager.

CGame::~CGame() {
	delete m_pObjectManager;
} //destructor

/// Initialize the renderer and the object manager, load
/// images and sounds, and begin the game.

void CGame::Initialize() {
	worldGenerator.srand(96549849); //seed should be chosen by the user. the user is suggested a random see at default
	m_pRenderer = new CRenderer;
	m_pRenderer->Initialize(512 + static_cast<int>(NUM_SPRITES));
	m_pRenderer->LoadImages(); //load images from xml file list

	m_pObjectManager = new CObjectManager; //set up object manager
	m_pTileManager = new TileManager(worldGenerator.randn(1, 1000000), 100);
	m_pAudio->Load(); //load the sounds for this game
	
	BeginGame();

} //Initialize

/// Release all of the DirectX12 objects by deleting the renderer.

void CGame::Release() {
	delete m_pRenderer;
	delete m_pTileManager;
	m_pTileManager = nullptr;
	m_pRenderer = nullptr; //for safety
} //Release

/// Ask the object manager to create the game objects.
/// There's only one in this game, the rotating
/// wheel o' text.

void CGame::CreateObjects() {

	m_pObjectManager->createEnvironment();

	//m_pObjectManager->create(START_PAGE4, Vector3(1, 1990.0f, 100.0f));
	m_pObjectManager->create(BOAT1, Vector3(-770, 303, 1988.0f)); //i know that the hook goes through it.
	m_pObjectManager->create(DOCK_SPRITE, Vector3(0, -467.0, 1990.0f));
	PC = m_pObjectManager->create(PENGUIN_STOP_SPRITE, Vector3(0, 0, 1990.0f));
	penguin = PC;

	m_pObjectManager->create(DOCK_BACK, Vector3(0, -460.0, 2050.0f));
	m_pObjectManager->create(CONNECTING_DOCK_SPRITE, Vector3(0, -10, 2100));
	m_pObjectManager->create(ISLAND_SPRITE, Vector3(0, 210.0, 2198.0f));
	
	
	//m_pObjectManager->create(BOAT2, Vector3(600.0, 80.0, 2150.0f));
	//m_pObjectManager->create(BOAT11, Vector3(600.0, 90.0, 2150.0f));


	CreateMenu();

	//this absolutely must be the last object created!
	Vector3 fishPos = Vector3(0, 0, 1989);
	int minY = 10000;
	for (int i = 0; i < numFish; ++i)
	{
		//this is testing, values need to be changed to a relative variable
		int x = (worldGenerator.randn() % int(m_fWorldWidth)) - int(m_fWorldWidth / 2);
		int y = (worldGenerator.randn() % minY) - 10300;
		fishPos.x = x;
		fishPos.y = y;
		int n = worldGenerator.randn(1, 100000000);

		fish = m_pObjectManager->createFish(fishPos, n);

	}
} //CreateObjects

void CGame::CreateMenu()
{
	menu = m_pObjectManager->createMenu(Vector3(PC->m_vPos.x + 459, PC->m_vPos.x + 26, 1000.0f));
}

void CGame::resetPC()
{
	PC = penguin;
	isFishing = false;
	PC->m_nSpriteIndex = PENGUIN_STOP_SPRITE;
}

/// Call this function to start a new game. This
/// should be re-entrant so that you can restart a
/// new game without having to shut down and restart the
/// program, but it's moot here. All we really need
/// to do is clear any old objects out of the object manager
/// and create some new ones.

void CGame::BeginGame() {
	m_pObjectManager->clear(); //clear old objects
	m_pAudio->loop(WAVES);
	CreateObjects(); //create new objects
} //BeginGame

/// Poll the keyboard state and respond to the
/// key presses that happened since the last frame.

void CGame::KeyboardHandler() {
	m_pKeyboard->GetState(); //get current keyboard state

	dialogOpen = menu->isDialogOpen;

	POINT p, q, r;
	p.x = 0; p.y = 0;
	ScreenToClient(m_Hwnd, &p);
	GetCursorPos(&q);
	r.x = p.x + q.x;
	r.y = p.y + q.y;

	if (!isFishing && !dialogOpen)
	{
		if (m_pKeyboard->TriggerDown(VK_F2))
		{
			if (isDebug) resetPC();
			isDebug = !isDebug;
		}
		if (m_pKeyboard->TriggerDown('A'))
		{
			if (menuOpen) menuOpen = menu->toggleMenu(p);
			PC->m_nSpriteIndex = PENGUIN_LEFT_SPRITE;
			if (isDebug) PC->SetSpeed(5);
			else PC->SetSpeed(1);
		}
		else if (m_pKeyboard->TriggerDown('D'))
		{
			if (menuOpen) menuOpen = menu->toggleMenu(p);
			PC->m_nSpriteIndex = PENGUIN_RIGHT_SPRITE;
			if (isDebug) PC->SetSpeed(5);
			else PC->SetSpeed(1);
		}
		else if (m_pKeyboard->TriggerDown('S') && isDebug)
		{
			if (menuOpen) menuOpen = menu->toggleMenu(p);
			PC->m_nSpriteIndex = PENGUIN_STOP_SPRITE;
			PC->SetSpeed(-5);
		}
		else if (m_pKeyboard->TriggerDown('W') && isDebug)
		{
			if (menuOpen) menuOpen = menu->toggleMenu(p);
			PC->m_nSpriteIndex = PENGUIN_STOP_SPRITE;
			PC->SetSpeed(5);
		}

		if (m_pKeyboard->TriggerDown('E'))
		{
			if (menuOpen) menuOpen = menu->toggleMenu(p);
			if ((PC->m_nSpriteIndex == PENGUIN_STOP_SPRITE) || (PC->m_nSpriteIndex == PENGUIN_LEFT_SPRITE) || (PC->m_nSpriteIndex == PENGUIN_RIGHT_SPRITE))
			{
				m_pObjectManager->boardBoat(true);
			}
		}
		if (m_pKeyboard->TriggerDown(VK_SHIFT))
		{
			if (menuOpen) menuOpen = menu->toggleMenu(p);
			m_pObjectManager->boardBoat(false);
		}

		if (m_pKeyboard->TriggerUp('A') || m_pKeyboard->TriggerUp('D') || m_pKeyboard->TriggerUp('W') || m_pKeyboard->TriggerUp('S'))
		{
			PC->m_nSpriteIndex = PENGUIN_STOP_SPRITE;
			PC->SetSpeed(0);
		}

		if (m_pKeyboard->TriggerDown('I'))
		{
			menuOpen = menu->toggleMenu(INVENTORY_MENU);
		}
		else if (m_pKeyboard->TriggerDown('B'))
		{
			menuOpen = menu->toggleMenu(BREEDING_MENU);
		}
	}

	if (!dialogOpen)
	{
		if (m_pKeyboard->TriggerDown(VK_LBUTTON))
		{
			if (m_pKeyboard->Down(VK_LSHIFT) && isFishing) //method to cut the line because of an arsehole fish
			{
				if (PC->m_nSpriteIndex >= NUM_SPRITES) //we should only cut the line if a fish is on it, why would you cut a line otherwise?
				{
					PC->isHooked = false;
					Vector3 anchor = PC->anchorPoint;
					PC = m_pObjectManager->create(HOOK_SPRITE, PC->m_vPos, true);
					PC->anchorPoint = anchor; //so the broken line goes back to the penguin instead of 0,0,0.

					//next we can change the hook to a white line (same color as cast line)
					PC->m_nSpriteIndex = WHITE_LINE;
					PC->SetSpeed(-10);
				}
			}
			else if (PC->isHooked)
			{
				PC->SetSpeed(0.6);//this should be a variable depending on type of fishing pole;
			}
			else
			{
				if ((r.x >= m_nWinWidth * 0.96640625) && (r.x <= m_nWinWidth) && (r.y >= m_nWinHeight * 0.0097222) && (r.y <= m_nWinHeight * 0.2347222) && (menuOpen == false))
					menuOpen = menu->toggleMenu(r);
				else if ((r.x >= m_nWinWidth * 0.78359375) && (r.x <= m_nWinWidth * 0.815625) && (r.y >= m_nWinHeight * 0.0097222) && (r.y <= m_nWinHeight * 0.2347222) && (menuOpen == true))
					menuOpen = menu->toggleMenu(r);
				else if ((r.x >= m_nWinWidth * 0.81640625) && (r.x <= m_nWinWidth) && (r.y >= 0) && (r.y <= m_nWinHeight * 0.8833333) && (menuOpen == true))
				{
					menu->sendMouseClick(r);
				}
				else if (isFishing == false)
				{
					if (menuOpen) menuOpen = menu->toggleMenu(p);
					isFishing = true;
					PC->m_nSpriteIndex = PENGUIN_FISHING_SPRITE;
					PC = m_pObjectManager->create(HOOK_SPRITE, Vector3(PC->m_vPos.x, PC->m_vPos.y, 1986));
					PC->SetSpeed(0.5);//this is depending on the sink
				}
			}
		}
	}
	else
	{
		if (m_pKeyboard->TriggerDown(VK_LBUTTON))
		{
			menu->sendMouseClick(r); //this will send the click to the dialog box because the dialog is currently open.
		}
	}
	if (m_pKeyboard->TriggerUp(VK_LBUTTON))
	{
		if (PC->isHooked)
		{
			PC->SetSpeed(0);
		}
		else
		{
			if (PC->m_nSpriteIndex == HOOK_SPRITE)
				PC->SetSpeed(-10);
		}
	}

	if (menuOpen)
	{
		
		menu->sendMouseHover(r);
	}
} //KeyboardHandler

/// Draw the current frame rate to a hard-coded position in the window.

//TO CHRISTY: Is this the one for text that rotates for Blank Game?
void CGame::DrawFrameRateText() {
	const string s = to_string(m_pStepTimer->GetFramesPerSecond()) + " fps";
	const Vector2 pos(m_nWinWidth - 128.0f, 30.0f);
	m_pRenderer->DrawScreenText(s.c_str(), pos);
} //DrawFrateRateText

//GLORIA'S TODO: modify below to work with a bait object <-- NEED TO CREATE
void CGame::ShootBait() {
	Vector3 pos, direction; //gun's muzzle position and direction

	//m_pPlane->GetGunMuzzle(pos, direction); //query plane for them
	//const Vector3 norm(direction.y, -direction.x, 0.0f); //normal to direction
	//CObject* p = m_pObjectManager->Create(BULLET_SPRITE, pos); //create bullet

	//const float m = 2.0f * m_pRandom->randf() - 1.0f;
	//direction += 0.01f * m * norm;
	//p->SetVel(m_pPlane->GetVel() + 400.0f * direction);

	//p->SetRoll(m_pPlane->GetRoll()); //bullet has same orientation as plane
	//p->SetLifeTime(0.4f + 0.1f * m_pRandom->randf());

	//m_pPlane->GunFireFx();
} //FireGun

/// Ask the object manager to draw the game objects. The renderer
/// is notified of the start and end of the frame so
/// that it can let Direct3D do its pipelining jiggery-pokery.

void CGame::RenderFrame() {
	m_pRenderer->BeginFrame();
	//m_pRenderer->Draw(TEST_SPRITE, m_vWinCenter); //draw background
	m_pObjectManager->DrawBackground();
	m_pObjectManager->draw(); //draw objects
	m_pObjectManager->DrawForeground();
	if (m_bDrawFrameRate)DrawFrameRateText(); //draw frame rate, if required
	m_pRenderer->EndFrame();
} //RenderFrame

/// Handle keyboard input, move the game objects and render
/// them in their new positions and orientations. Notify the
/// audio player at the start of each frame so that it can
/// prevent multiple copies of a sound from starting on the
/// same frame. Notify the timer of the start and end of the
/// frame so that it can calculate frame time.

void CGame::FollowCamera() {
	Vector3 vCameraPos(PC->GetPos()); //player position when not fishing
	m_pRenderer->SetCameraPos(Vector3(vCameraPos.x, vCameraPos.y, 0.01f)); //camera to player

	//if penguin is out the dock, display the boat
	/*if ((vCameraPos.x > 800 || vCameraPos.x < -800) && moving_boat == false)
	{
		//display the moving boat that follows the penguin
		boat = m_pObjectManager->create(BOAT2, Vector3(penguin->GetPos().x, -10.0, 1950.0f));
		moving_boat = true;
	}
	//if penguin is on the dock, remove the boat
	else if ((vCameraPos.x <= 800 || vCameraPos.x >= -800) && moving_boat == true)
	{
		//remove the moving boat that follows the penguin
		boat->kill();
		moving_boat = false;
	}*/
} //FollowCamera

void CGame::ProcessFrame() {
	KeyboardHandler(); //handle keyboard input

	m_pAudio->BeginFrame(); //notify audio player that frame has begun

	m_pStepTimer->Tick([&]() {
		if(m_pStepTimer->GetTotalSeconds() > m_fFrameTimer + 180) {
			m_fFrameTimer = m_pStepTimer->GetTotalSeconds();
			if (worldGenerator.randn() % 2 == 0) m_pAudio->play(OCEAN1_THEME, 1.2);
		} //if

		if (PC->isCaught)
		{			
			//reset 
			resetPC();
			menu->setInventoryPositions();
		}
		else if (PC->IsDead()) resetPC();

		m_pObjectManager->move(); //move all objects
		FollowCamera();
		});

	RenderFrame(); //render a frame of animation
}//ProcessFrame