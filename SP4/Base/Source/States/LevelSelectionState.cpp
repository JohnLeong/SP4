#include <iostream>
using namespace std;

#include "../Application.h"
#include "GameStateManager.h"
#include "playstate.h"
#include "gamestate.h"
#include "LevelSelectionState.h"
#include "MenuState.h"

CLevelSelectionState CLevelSelectionState::theLevelSelectionState;

void CLevelSelectionState::Init()
{
#if _DEBUG
	cout << "CLevelSelectionState::Init" << endl;
#endif

	scene = new CSceneLevelSelection(1280, 720);
	scene->Init();
}

void CLevelSelectionState::Init(const int width, const int height)
{
#if _DEBUG
	cout << "CLevelSelectionState::Init" << endl;
#endif

	scene = new CSceneLevelSelection(width, height);
	scene->Init();
}

void CLevelSelectionState::Cleanup()
{
#if _DEBUG
	cout << "CLevelSelectionState::Cleanup" << endl;
#endif
}

void CLevelSelectionState::Pause()
{
#if _DEBUG
	cout << "CLevelSelectionState::Pause" << endl;
#endif
}

void CLevelSelectionState::Resume()
{
#if _DEBUG
	cout << "CLevelSelectionState::Resume" << endl;
#endif
}

void CLevelSelectionState::HandleEvents(CGameStateManager* theGSM)
{
#if _DEBUG
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CLevelSelectionState: Choose one <0> Go to Intro State, <1> Go to Play State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CIntroState::Instance() );
	//			break;

	//		case 1:
	//			theGSM->ChangeState( CPlayState::Instance() );
	//			break;
	//		default:
	//			cout << "Invalid choice!\n";
	//			m_iUserChoice = -1;
	//			break;
	//	}
	//} while (m_iUserChoice == -1);
#endif
}

void CLevelSelectionState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
	if (key == 'B' && status)
	{
		theGSM->ChangeState(CMenuState::Instance());
	}
	if (key == 'F' && status)
	{
		Application::m_bChangeRes = true;
	}

	scene->SetKeyDown(key, status);
}

void CLevelSelectionState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{

}

void CLevelSelectionState::Update(CGameStateManager* theGSM)
{
#if _DEBUG
	cout << "CLevelSelectionState::Update" << endl;
#endif
	scene->Update(0.16667);
}

void CLevelSelectionState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);

	if (CSceneLevelSelection::GetIsQuitToMain() == true)
	{
		theGSM->ChangeState(CMenuState::Instance());
	}

	if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 1
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 1)
		theGSM->ChangeState(CPlayState::Instance());
}

void CLevelSelectionState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}
