#include <iostream>
using namespace std;

#include "gamestate.h"
#include "GameStateManager.h"
#include "playstate.h"
#include "menustate.h"
#include "FinishState.h"

CPlayState CPlayState::thePlayState;

void CPlayState::Init()
{
#if _DEBUG
	cout << "CPlayState::Init" << endl;
#endif

	#if TYPE_OF_VIEW == 3
		scene = new CScenePlay(1280, 720);	// Use this for 3D gameplay
	#else
		scene = new CSceneManager2D(800, 600);	// Use this for 2D gameplay
	#endif
	scene->Init();
}

void CPlayState::Init(const int width, const int height)
{
#if _DEBUG
	cout << "CPlayState::Init" << endl;
#endif

	scene = new CScenePlay(width, height);	// Use this for 3D gameplay

	scene->Init();
}

void CPlayState::InitHoldData(int width, int height, int i, bool b)
{
#if _DEBUG
	cout << "CPlayState::Init" << endl;
#endif

	scene = new CScenePlay(width, height);	// Use this for 3D gameplay

	scene->Init();
}

void CPlayState::Cleanup()
{
#if _DEBUG
	cout << "CPlayState::Cleanup" << endl;
#endif
	// Delete the scene
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CPlayState::Pause()
{
#if _DEBUG
	cout << "CPlayState::Pause" << endl;
#endif
}

void CPlayState::Resume()
{
#if _DEBUG
	cout << "CPlayState::Resume" << endl;
#endif
}

void CPlayState::HandleEvents(CGameStateManager* theGSM)
{
#if _DEBUG
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CPlayState: Choose one <0> Go to Menu State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CMenuState::Instance() );
	//			break;
	//		default:
	//			cout << "Invalid choice!\n";
	//			m_iUserChoice = -1;
	//			break;
	//	}
	//} while (m_iUserChoice == -1);
#endif
}

void CPlayState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
	scene->SetKeyDown(key, status);
}

void CPlayState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{
#if _DEBUG
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CPlayState: Choose one <0> Go to Menu State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CMenuState::Instance() );
	//			break;
	//		default:
	//			cout << "Invalid choice!\n";
	//			m_iUserChoice = -1;
	//			break;
	//	}
	//} while (m_iUserChoice == -1);
#endif
	if (button_Left == 1)
		scene->UpdateWeaponStatus(scene->WA_FIRE);
	else if (button_Right == 1)
		scene->UpdateWeaponStatus(scene->WA_FIRE_SECONDARY);
}


void CPlayState::Update(CGameStateManager* theGSM)
{
#if _DEBUG
	//cout << "CPlayState::Update\n" << endl;
#endif
	// Update the scene
	scene->Update(0.16667);
}

void CPlayState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	// Update the scene
	scene->Update(m_dElapsedTime);

	if (CScenePlay::GetIsQuitToMain() == true)
	{
		//scene->Exit();
		theGSM->ChangeState(CMenuState::Instance());
	}
	else if (static_cast<CScenePlay*>(scene)->m_bToFinishScreen == true)
	{
		theGSM->ChangeState(CFinishState::Instance());
	}
}

void CPlayState::Draw(CGameStateManager* theGSM)
{
	// Render the scene
	scene->Render();
}
