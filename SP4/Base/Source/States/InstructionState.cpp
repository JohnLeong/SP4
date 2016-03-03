#include <iostream>
using namespace std;

#include "../Application.h"
#include "GameStateManager.h"
#include "playstate.h"
#include "gamestate.h"
#include "InstructionState.h"
#include "MenuState.h"

CInstructionState CInstructionState::theInstructionState;

void CInstructionState::Init()
{
#if _DEBUG
	cout << "CInstructionState::Init" << endl;
#endif

	scene = new CSceneInstruction(1280, 720);
	scene->Init();
}

void CInstructionState::Init(const int width, const int height)
{
#if _DEBUG
	cout << "CInstructionState::Init" << endl;
#endif

	scene = new CSceneInstruction(width, height);
	scene->Init();
}

void CInstructionState::Cleanup()
{
#if _DEBUG
	cout << "CInstructionState::Cleanup" << endl;
#endif
	// Delete the scene
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CInstructionState::Pause()
{
#if _DEBUG
	cout << "CInstructionState::Pause" << endl;
#endif
}

void CInstructionState::Resume()
{
#if _DEBUG
	cout << "CInstructionState::Resume" << endl;
#endif
}

void CInstructionState::HandleEvents(CGameStateManager* theGSM)
{
#if _DEBUG
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CInstructionState: Choose one <0> Go to Intro State, <1> Go to Play State : " ;
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

void CInstructionState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
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

void CInstructionState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{

}

void CInstructionState::Update(CGameStateManager* theGSM)
{
#if _DEBUG
	cout << "CInstructionState::Update" << endl;
#endif
	scene->Update(0.16667);
}

void CInstructionState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);
	if (((CSceneInstruction*)scene)->m_bChangeState)
	{
		theGSM->ChangeState(CMenuState::Instance());
	}
	//if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 1
	//	|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 1)
	//	theGSM->ChangeState(CMenuState::Instance());
}

void CInstructionState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}
