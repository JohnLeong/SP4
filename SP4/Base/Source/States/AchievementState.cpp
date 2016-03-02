#include <iostream>
using namespace std;

#include "../Application.h"
#include "GameStateManager.h"
#include "playstate.h"
#include "gamestate.h"
#include "AchievementState.h"
#include "MenuState.h"

CAchievementState CAchievementState::theAchievementState;

void CAchievementState::Init()
{
#if _DEBUG
	cout << "CAchievementState::Init" << endl;
#endif

	scene = new CSceneAchievements(1280, 720);
	scene->Init();
}

void CAchievementState::Init(const int width, const int height)
{
#if _DEBUG
	cout << "CAchievementState::Init" << endl;
#endif

	scene = new CSceneAchievements(width, height);
	scene->Init();
}

void CAchievementState::Cleanup()
{
#if _DEBUG
	cout << "CAchievementState::Cleanup" << endl;
#endif
}

void CAchievementState::Pause()
{
#if _DEBUG
	cout << "CAchievementState::Pause" << endl;
#endif
}

void CAchievementState::Resume()
{
#if _DEBUG
	cout << "CAchievementState::Resume" << endl;
#endif
}

void CAchievementState::HandleEvents(CGameStateManager* theGSM)
{
#if _DEBUG
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CAchievementState: Choose one <0> Go to Intro State, <1> Go to Play State : " ;
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

void CAchievementState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
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

void CAchievementState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{

}

void CAchievementState::Update(CGameStateManager* theGSM)
{
#if _DEBUG
	cout << "CAchievementState::Update" << endl;
#endif
	scene->Update(0.16667);
}

void CAchievementState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);

	if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 1
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 1)
		theGSM->ChangeState(CMenuState::Instance());
}

void CAchievementState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}
