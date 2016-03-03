#include <iostream>
using namespace std;

#include "../Application.h"
#include "GameStateManager.h"
#include "playstate.h"
#include "gamestate.h"
#include "FinishState.h"
#include "MenuState.h"

CFinishState CFinishState::theFinishState;

void CFinishState::Init()
{
#if _DEBUG
	cout << "CFinishState::Init" << endl;
#endif

	scene = new CSceneFinish(1280, 720);
	scene->Init();
}

void CFinishState::Init(const int width, const int height)
{
#if _DEBUG
	cout << "CFinishState::Init" << endl;
#endif
	isConfirmsoundPlaying = false;
	scene = new CSceneFinish(width, height);
	scene->Init();
}

void CFinishState::Cleanup()
{
#if _DEBUG
	cout << "CFinishState::Cleanup" << endl;
#endif
	// Delete the scene
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CFinishState::Pause()
{
#if _DEBUG
	cout << "CFinishState::Pause" << endl;
#endif
}

void CFinishState::Resume()
{
#if _DEBUG
	cout << "CFinishState::Resume" << endl;
#endif
}

void CFinishState::HandleEvents(CGameStateManager* theGSM)
{
#if _DEBUG
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CFinishState: Choose one <0> Go to Intro State, <1> Go to Play State : " ;
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

void CFinishState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
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

void CFinishState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{

}

void CFinishState::Update(CGameStateManager* theGSM)
{
#if _DEBUG
	cout << "CFinishState::Update" << endl;
#endif
	scene->Update(0.16667);
}

void CFinishState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);

	if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 1
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 1)
	{
		if (isConfirmsoundPlaying == false)
		{
			Application::Sound.playSound("../irrKlang/media/confirm_sound.wav");
			isConfirmsoundPlaying = true;
		}

		theGSM->ChangeState(CMenuState::Instance());
	}
}

void CFinishState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}
