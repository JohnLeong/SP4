#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "playstate.h"
#include "gamestate.h"
#include "menustate.h"
#include "OptionsState.h"
#include "InstructionState.h"
#include "LevelSelectionState.h"
#include "AchievementState.h"
#include "../Application.h"

CMenuState CMenuState::theMenuState;

void CMenuState::Init()
{
#if _DEBUG
	cout << "CMenuState::Init" << endl;
#endif

	scene = new CSceneMenu();
	scene->Init();
}

void CMenuState::Init(const int width, const int height)
{
#if _DEBUG
	cout << "CMenuState::Init" << endl;
#endif

	scene = new CSceneMenu();
	scene->Init();
}

void CMenuState::Cleanup()
{
#if _DEBUG
	cout << "CMenuState::Cleanup" << endl;
#endif
}

void CMenuState::Pause()
{
#if _DEBUG
	cout << "CMenuState::Pause" << endl;
#endif
}

void CMenuState::Resume()
{
#if _DEBUG
	cout << "CMenuState::Resume" << endl;
#endif
}

void CMenuState::HandleEvents(CGameStateManager* theGSM)
{
#if _DEBUG
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CMenuState: Choose one <0> Go to Intro State, <1> Go to Play State : " ;
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

void CMenuState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
	scene->SetKeyDown(key, status);
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{

}

void CMenuState::Update(CGameStateManager* theGSM) 
{
#if _DEBUG
	cout << "CMenuState::Update" << endl;
#endif
	scene->Update(0.16667);

	
	if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 1
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 1)
		theGSM->ChangeState(CLevelSelectionState::Instance());
	else if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 2
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 2)
		theGSM->ChangeState(CInstructionState::Instance());
	else if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 3
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 3)
		theGSM->ChangeState(COptionsState::Instance());
	else if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 4
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 4)
		exit(0);
	else if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 5
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 5)
		theGSM->ChangeState(CAchievementState::Instance());
}

void CMenuState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);

	if (((CSceneMenu*)scene)->m_bChangeState)
	{
		std::cout << "CHANGE";
		switch (((CSceneMenu*)scene)->m_iNextState)
		{
		case CSceneMenu::NEXT_LEVEL_SELECT:
			theGSM->ChangeState(CLevelSelectionState::Instance());
			break;
		case CSceneMenu::NEXT_INSTRUCTIONS:
			theGSM->ChangeState(CInstructionState::Instance());
			break;
		case CSceneMenu::NEXT_OPTIONS:
			theGSM->ChangeState(COptionsState::Instance());
			break;
		case CSceneMenu::NEXT_ACHIEVEMENT:
			theGSM->ChangeState(CAchievementState::Instance());
			break;
		case CSceneMenu::NEXT_EXIT:
			Application::AppisRunning = false;
			break;
		default:
			break;
		}
	}

	/*if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 1 
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 1)
	{
		theGSM->ChangeState(CLevelSelectionState::Instance());
	}
	else if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 2
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 2)
		theGSM->ChangeState(CInstructionState::Instance());
	else if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 3
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 3)
		theGSM->ChangeState(COptionsState::Instance());
	else if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 4
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 4)
		exit(0);*/
}

void CMenuState::Draw(CGameStateManager* theGSM) 
{
	scene->Render();
}
